#include <DiscodelicLib.h>

const int numPanels = 3;
const int worldSize = NUM_ROWS * NUM_LEDS * numPanels;
const long updatePeriod = 100 * 1000l; // 10 Hz

#define colorSnake (RGB2color(MAX_BRIGHT / 2, 0, 0))
#define colorBlack (RGB2color(0, 0, 0))
#define colorField (RGB2color(0, MAX_BRIGHT / 2, MAX_BRIGHT / 3))
#define colorFood (RGB2color(MAX_BRIGHT / 2, 0, MAX_BRIGHT / 2))
#define colorHead (RGB2color(MAX_BRIGHT - 1, MAX_BRIGHT - 2, 0))
#define colorDead (RGB2color(1, 1, 1))

enum {
  DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
};

enum {
  top, front, right
};

PanelId toPanel(int panel) {
  switch(panel) {
    case top:   return PANEL_TOP;
    case front: return PANEL_FRONT;
    case right: return PANEL_RIGHT;
    default:    return PANEL_BACK;
  }
}

class FieldLoc {
  public:
  uint8_t panel : 2, // 0:PANEL_TOP, 1:PANEL_FRONT, 2:PANEL_RIGHT, 3:DEAD
          x : 3, y : 3;

  FieldLoc() : panel(top), x(0), y(0) { }
  FieldLoc(int _panel, int _x, int _y);
  bool operator== (const FieldLoc & other);
  bool operator!= (const FieldLoc & other);
  FieldLoc & operator= (const FieldLoc & other);
  bool move(int direction, FieldLoc & result);
  int getPeers(FieldLoc peers[]);

  void draw(uint16_t color) {
    FieldLoc peers[3];
    int numPeers = getPeers(peers);
    peers[numPeers++] = *this;
    for (int peerNdx = 0; peerNdx < numPeers; ++peerNdx) {
      FieldLoc peer = peers[peerNdx];
      Panel *pPanel = Discodelic1.getPanel(FRAME_NEXT, toPanel(peer.panel));
      Vector *pRow = pPanel->getRow(peer.y);
      pRow->setLed(peer.x, color);
    }
  }

  void print() {
    Serial.print(panel);
    Serial.print(":");
    Serial.print(x);
    Serial.print(":");
    Serial.print(y);
  }
};


FieldLoc::FieldLoc(int _panel, int _x, int _y) : panel(_panel), x(_x), y(_y) { }

bool FieldLoc::operator== (const FieldLoc & other) {
  if (this == &other) {
    return true;
  }

  FieldLoc peers[3];
  int numPeers = getPeers(peers);
  peers[numPeers++] = *this;
  for (int peerNdx = 0; peerNdx < numPeers; ++peerNdx) {
    FieldLoc peer = peers[peerNdx];
    if (peer.panel == other.panel) {
      return (peer.x == other.x) && (peer.y == other.y);
    }
  }
  
  return false;
}

bool FieldLoc::operator!= (const FieldLoc & other) {
  return !(*this == other);
}

FieldLoc & FieldLoc::operator= (const FieldLoc & other) {
  if (this != &other) {
    panel = other.panel;
    x = other.x;
    y = other.y;
  }
  return *this;
}

bool skipNdx(int ndx) {
  switch (ndx) {
    case 1:
    case 3:
    case 4:
    case 6:
      return true;
    default:
      return false;
  }
}

bool FieldLoc::move(int direction, FieldLoc &result) {
  result = *this;
  switch (panel) {
    case top:
      if ((x == 0 && direction == DIR_LEFT) || (y == 0 && direction == DIR_UP)) {
        return true;
      } else if (x == MAX_LED && direction == DIR_RIGHT) {
        result.panel = right;
        result.x = MAX_LED - y;
        result.y = 1;
        break;
      } else if (y == MAX_LED && direction == DIR_DOWN) {
        result.panel = front;
        result.x = x;
        result.y = 1;
        break;
      }
      break;
    case front:
      if ((x == 0 && direction == DIR_LEFT) || (y == 7 && direction == DIR_DOWN)) {
        return true;
      } else if (x == MAX_LED && direction == DIR_RIGHT) {
        result.panel = right;
        result.x = 1;
        break;
      } else if (y == 0 && direction == DIR_UP) {
        result.panel = top;
        result.x = x;
        result.y = 6;
        break;
      }
      break;
    case right:
      if ((x == MAX_LED && direction == DIR_RIGHT) || (y == 7 && direction == DIR_DOWN)) {
        return true;
      } else if (x == 0 && direction == DIR_LEFT) {
        result.panel = front;
        result.x = 6;
        break;
      } else if (y == 0 && direction == DIR_UP) {
        result.panel = top;
        result.x = 6;
        result.y = MAX_LED - x;
        break;
      }
      break;
  }
  if (result.panel == panel) {

    // Did not change panels
    switch (direction) {
      case DIR_UP:    result.y = y - 1; break;
      case DIR_DOWN:  result.y = y + 1; break;
      case DIR_LEFT:  result.x = x - 1; break;
      case DIR_RIGHT: result.x = x + 1; break;
    }
  }
  return skipNdx(result.x) && skipNdx(result.y);
}

int FieldLoc::getPeers(FieldLoc peers[]) {
  int peersNdx = 0;
  if (panel == top) {
    if (x == MAX_LED) {
      peers[peersNdx++] = FieldLoc(right, MAX_LED - y, 0);
    }
    if (y == MAX_LED) {
      peers[peersNdx++] = FieldLoc(front, x, 0);
    }
  } else if (panel == front) {
    if (x == MAX_LED) {
      peers[peersNdx++] = FieldLoc(right, 0, y);
    }
    if (y == 0) {
      peers[peersNdx++] = FieldLoc(top, x, MAX_LED);
    }
  } else if (panel == right) {
    if (x == 0) {
      peers[peersNdx++] = FieldLoc(front, MAX_LED, y);
    }
    if (y == 0) {
      peers[peersNdx++] = FieldLoc(top, MAX_LED, MAX_LED - x);
    }
  }
  return peersNdx;
}

FieldLoc food;

class Snake {
  public:
    FieldLoc body[worldSize];
    uint8_t head = 0, tail = 0;
    int direction;
    bool dead = false;

  void move() {
    FieldLoc oldHead = body[head];
    FieldLoc newHead;
    dead = oldHead.move(direction, newHead);
    if (dead) {
      return;
    }

    if ((newHead.panel == top) && (oldHead.panel == right)) {
      direction = DIR_LEFT;
    } else if ((newHead.panel == right) && (oldHead.panel == top)) {
      direction = DIR_DOWN;
    } 

    ++head;
    if (head == worldSize) {
      head = 0;
    }
    body[head] = newHead;

    if (newHead != food) {
      ++tail;
      if (tail == worldSize) {
        tail = 0;
      }
    }
  }

  void draw() {
    uint16_t color = dead ? colorDead : colorSnake;
    int bodyNdx = tail;
    while (bodyNdx != head) {
      body[bodyNdx].draw(color);
      ++bodyNdx;
      if (bodyNdx == worldSize) {
        bodyNdx = 0;
      }
    }
    body[head].draw(colorHead);
  }

  void print() {
    for (int bodyNdx = tail; bodyNdx != head; bodyNdx = (bodyNdx + 1) % worldSize) {
      Serial.print(bodyNdx);
      Serial.print(":");
      body[bodyNdx].print();
      Serial.println();
    }
    Serial.print(head);
    Serial.print("H");
    body[head].print();
    Serial.println();
  }
};

Snake snake;

const int numFaces = 3;
PanelId faces[numFaces] = {PANEL_TOP, PANEL_FRONT, PANEL_RIGHT};

void blankCube() {
  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    DiscodelicGfx1.setGfxPanel(panelId);
    DiscodelicGfx1.fillScreen(colorBlack);
  }
}

void drawField() {
  for (FrameId frameId = FRAME_CURRENT; frameId <= FRAME_NEXT; ++frameId) {
    for (int panelNdx = 0; panelNdx < numFaces; ++panelNdx) {
      Panel *pPanel = Discodelic1.getPanel(frameId, toPanel(panelNdx));
      for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
        Vector *pRow = pPanel->getRow(rowNdx);
        for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
          if (skipNdx(rowNdx) && skipNdx(ledNdx)) {
            continue;
          }
          pRow->setLed(ledNdx, colorField);
        }
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  Discodelic1.setup();
//  Discodelic1.dumpAllPanels();

  snake.body[snake.head] = FieldLoc(top, 2, 2);
  snake.direction = DIR_DOWN;

  food = FieldLoc(front, 5, 5);

  blankCube();
  drawField();
  snake.draw();
  food.draw(colorFood);

  Discodelic1.swapBuffers(true);

  blankCube();
  drawField();
  snake.draw();
  food.draw(colorFood);

  Discodelic::registerCallback(updatePeriod, animate);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SWITCH) == LOW) {
    randomSeed(micros());
  }
  Discodelic1.refresh();
}

const int movePeriod = 4; // 1 second
int stepCount = 0;

bool animate() {
  ++stepCount;

  drawField();
  if (stepCount % 3 == 0) {
    food.draw(colorField);
  } else {
    food.draw(colorFood);
  }

  if ((stepCount == movePeriod) && !snake.dead) {
    stepCount = 0;

    // REMOVE when buttons
    FieldLoc headLoc = snake.body[snake.head];
    FieldLoc nextLoc;

    int startDirection = random(0, 4);
    int direction = startDirection;
    bool found = false;
    do {
      if ((snake.direction == DIR_UP && direction == DIR_DOWN) ||
        (snake.direction == DIR_DOWN && direction == DIR_UP) ||
        (snake.direction == DIR_LEFT && direction == DIR_RIGHT) ||
        (snake.direction == DIR_RIGHT && direction == DIR_LEFT)) {
        direction = (direction + 1) % 4;
        continue;
      }
      bool dead = headLoc.move(direction, nextLoc);
Serial.print("direction=");
Serial.println(direction);
Serial.print("nextLoc=");
nextLoc.print();
Serial.println();
      if (!dead && !(skipNdx(nextLoc.x) && skipNdx(nextLoc.y))) {
        snake.direction = direction;
        found = true;
Serial.println();
      }
      direction = (direction + 1) % 4;
    } while (!found && (direction != startDirection));

    snake.dead = !found;
    
    if (!snake.dead) {
      for (int bodyNdx = snake.tail; bodyNdx != snake.head; bodyNdx = (bodyNdx + 1) % worldSize) {
        if (snake.body[bodyNdx] == nextLoc) {
          snake.dead = true;
          Serial.println("DEAD by self bite");
          Serial.print("nextLoc=");
          nextLoc.print();
          Serial.println();
          snake.print();
          break;
        }
      }
    } else {
      Serial.println("DEAD by no direction found");
      snake.print();
    }

    if (!snake.dead) {
      snake.move();

      if (snake.body[snake.head] == food) {
        FieldLoc startLoc = 
          FieldLoc(random(0,3), random(0, NUM_LEDS), random(0, NUM_ROWS));

        uint8_t x, y;
        uint8_t panel = startLoc.panel;
        found = false;
        do {
          x = startLoc.x;
          do {
            y = startLoc.y;
            do {
              if (!(skipNdx(x) && skipNdx(y))) {
                food = FieldLoc(panel, x, y);
                int bodyNdx;
                for (bodyNdx = snake.tail; bodyNdx != snake.head; bodyNdx = (bodyNdx + 1) % worldSize) {
                  if (snake.body[bodyNdx] == food) {
                    break;
                  }
                }
                if ((bodyNdx == snake.head) && (snake.body[bodyNdx] != food)) {
                  found = true;
                }
              }

              y = (y + 1) % NUM_ROWS;
            } while (!found && (y != startLoc.y));

            x = (x + 1) % NUM_LEDS;
          } while (!found && (x != startLoc.x));

          panel = (panel + 1) % 4;
        } while (!found && (panel != startLoc.panel));

        if (found) {
          food.draw(colorFood);
        } else {
          snake.dead = true;
        }
      }
    }
  }

  snake.draw();
  return true;
}

