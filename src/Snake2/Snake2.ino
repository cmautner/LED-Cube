#include <DiscodelicLib.h>

const int LEFT_BUTTON = 6;
const int COMMON = 5;
const int RIGHT_BUTTON = 4;

#define colorSnake (RGB2color(MAX_BRIGHT, 0, 0))
#define colorBlack (RGB2color(0, 0, 0))
#define colorField (RGB2color(1, 1, 1))
#define colorFood (RGB2color(0, MAX_BRIGHT - 1, 0))
#define colorHead (RGB2color(MAX_BRIGHT, MAX_BRIGHT - 1, 0))
#define colorTail (RGB2color(0, MAX_BRIGHT - 1, MAX_BRIGHT - 2))
#define colorDead (RGB2color(0, 0, 2))

class FieldLoc;
class Snake;

// Direction values
enum {
  DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT
};

// Panel values
enum {
  top, front, right, numPanels
};

const int worldSize = NUM_ROWS * NUM_LEDS * numPanels;
const long updatePeriod = 50 * 1000l;

PanelId toPanel(int panel) {
  switch(panel) {
    case top:   return PANEL_TOP;
    case front: return PANEL_FRONT;
    case right: return PANEL_RIGHT;
    default:    return PANEL_BACK;
  }
}

/*
 * (x,y) combinations containing both of these columns and rows
 * are not allowed. E.g. (4,6), (4,3) are not valid; (0,4), (7,5) are.
 */
bool skipNdx(int ndx) {
  if (digitalRead(SWITCH) == LOW) {
    return false;
  }
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

class FieldLoc {
  public:
  uint8_t panel : 2, // 0:PANEL_TOP, 1:PANEL_FRONT, 2:PANEL_RIGHT
          x : 3, y : 3;

  FieldLoc() : panel(top), x(0), y(0) { }
  FieldLoc(int _panel, int _x, int _y) : panel(_panel), x(_x), y(_y) { }

  static FieldLoc randomLoc() {
    while (true) {
      FieldLoc randLoc =
        FieldLoc(random(top,right + 1), random(0, NUM_LEDS), random(0, NUM_ROWS));
      if (!(skipNdx(randLoc.x) && skipNdx(randLoc.y))) {
        return randLoc;
      }
    }
  }

  bool operator== (const FieldLoc & other) {
    if (this == &other) {
      return true;
    }

    // Compare against all possible values that other could be.
    FieldLoc peers[3];
    int numPeers = getPeers(peers);
    for (int peerNdx = 0; peerNdx < numPeers; ++peerNdx) {
      FieldLoc peer = peers[peerNdx];
      if (peer.panel == other.panel) {
        return (peer.x == other.x) && (peer.y == other.y);
      }
    }

    return false;
  }

  bool operator!= (const FieldLoc & other) {
    return !(*this == other);
  }

  FieldLoc & operator= (const FieldLoc & other) {
    if (this != &other) {
      panel = other.panel;
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  /*
   * If this FieldLoc can legally move in the direction indicated then put the
   * result of that move into result. If the movement results in an illegal
   * location return true.
   */
  bool move(int direction, FieldLoc &result) {
    result = *this;
    // Handle movement from the edge of one panel into another panel.
    switch (panel) {
      case top:
        if ((x == 0 && direction == DIR_LEFT) || (y == 0 && direction == DIR_UP)) {
          return true;
        } else if (x == MAX_LED && direction == DIR_RIGHT) {
          result.panel = right;
          result.x = MAX_LED - y;
          result.y = 1;
        } else if (y == MAX_LED && direction == DIR_DOWN) {
          result.panel = front;
          result.x = x;
          result.y = 1;
        }
        break;
      case front:
        if ((x == 0 && direction == DIR_LEFT) || (y == 7 && direction == DIR_DOWN)) {
          return true;
        } else if (x == MAX_LED && direction == DIR_RIGHT) {
          result.panel = right;
          result.x = 1;
        } else if (y == 0 && direction == DIR_UP) {
          result.panel = top;
          result.x = x;
          result.y = 6;
        }
        break;
      case right:
        if ((x == MAX_LED && direction == DIR_RIGHT) || (y == 7 && direction == DIR_DOWN)) {
          return true;
        } else if (x == 0 && direction == DIR_LEFT) {
          result.panel = front;
          result.x = 6;
        } else if (y == 0 && direction == DIR_UP) {
          result.panel = top;
          result.x = 6;
          result.y = MAX_LED - x;
        }
        break;
    }

    if (result.panel == panel) {
      // Did not change panels, just modify the location in the passed direction.
      switch (direction) {
        case DIR_UP:    result.y = y - 1; break;
        case DIR_DOWN:  result.y = y + 1; break;
        case DIR_LEFT:  result.x = x - 1; break;
        case DIR_RIGHT: result.x = x + 1; break;
      }
    }
    return skipNdx(result.x) && skipNdx(result.y);
  }

  /*
   * Every edge location is mirrored on adjacent edges. The FieldLoc that is in the
   * corner of top, front, and right is shared between all three. For any FieldLoc
   * this function fills an array including the FieldLoc and all the FieldLocs on
   * other panels that are equivalent to it. The number of peers (1-3) is returned.
   */
  int getPeers(FieldLoc peers[]) {
    int peersNdx = 0;
    peers[peersNdx++] = *this;
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

  /*
   * Draw this FieldLoc and all of its peers.
   */
  void draw(uint16_t color) {
    FieldLoc peers[3];
    int numPeers = getPeers(peers);
    for (int peerNdx = 0; peerNdx < numPeers; ++peerNdx) {
      FieldLoc peer = peers[peerNdx];
      Panel *pPanel = Discodelic1.getPanel(FRAME_CURRENT, toPanel(peer.panel));
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
} food;

class Snake {
  public:
    FieldLoc body[worldSize];
    uint8_t head = 0, tail = 0;
    int direction;
    bool dead = false;
    long deadTime;

  void kill() {
    dead = true;
    deadTime = millis();
    srand(deadTime);
  }

  void move() {
    FieldLoc oldHead = body[head];
    FieldLoc newHead;

    // Make the move, but don't store the new location in the body.
    dead = oldHead.move(direction, newHead);
    if (dead) {
      kill();
      Serial.println("DEAD by move off field");
      Serial.print("newHead=");
      newHead.print();
      Serial.println();
      print();
      return;
    }

    // Change the direction appropriately if the FieldLoc changed from one panel
    // to another. By changing the logical direction the physical direction will
    // continue unchanged.
    if ((newHead.panel == top) && (oldHead.panel == right)) {
      direction = DIR_LEFT;
    } else if ((newHead.panel == right) && (oldHead.panel == top)) {
      direction = DIR_DOWN;
    }

    // Advance the head and store the new FieldLoc in the next entry.
    head = (head + 1) % worldSize;
    body[head] = newHead;

    // If the food is eaten, grow the snake by not updating tail. Otherwise
    // update the tail to the next entry.
    if (newHead != food) {
      tail = (tail + 1) % worldSize;
    }
  }

  void draw() {
    uint16_t color = colorTail;
    int bodyNdx = tail;
    while (bodyNdx != head) {
      body[bodyNdx].draw(color);
      bodyNdx = (bodyNdx + 1) % worldSize;
      color = dead ? colorDead : colorSnake;
    }
    body[head].draw(colorHead);
  }

  int length() {
    return (head + worldSize - tail) % worldSize;
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
} snake;


void drawCube() {
  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    DiscodelicGfx1.setGfxPanel(panelId);
    DiscodelicGfx1.fillScreen(colorBlack);
  }
}

void drawField() {
  for (FrameId frameId = FRAME_CURRENT; frameId < FRAME_NEXT; ++frameId) {
    for (int panelNdx = 0; panelNdx < numPanels; ++panelNdx) {
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

unsigned long nextMoveTime;

void reset() {
  snake = Snake();
  FieldLoc snakeHead;
  do {
    snakeHead = FieldLoc::randomLoc();
    food = FieldLoc::randomLoc();
  } while (food == snakeHead);

  snake.body[snake.head] = snakeHead;

  drawCube();
  drawField();
  snake.draw();
  food.draw(colorFood);

  Discodelic1.swapBuffers(true);

  drawCube();
  drawField();
  snake.draw();
  food.draw(colorFood);

  nextMoveTime = millis() + 1000;
}

void setup() {
  Serial.begin(115200);

  Discodelic1.setup();

  if (true || digitalRead(SWITCH) == HIGH) {
    long seed = 0;
    for (int i = 0; i < 10; ++i) {
      
      seed = (seed << 3) | (analogRead(A0) & 7);
      delay(1);
    }
    randomSeed(seed ^ micros());
  }

  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(COMMON, OUTPUT);
  digitalWrite(COMMON, LOW);

  reset();

  Discodelic::registerCallback(updatePeriod, animate);
}

unsigned long lastButtonTime;
int lastButtonPress;
int buttonDirection;

const char *directionStrings[] = {
  "DIR_UP", "DIR_DOWN", "DIR_LEFT", "DIR_RIGHT"
};

void loop() {
  noInterrupts();
  int left = digitalRead(LEFT_BUTTON) == HIGH;
  int right = digitalRead(RIGHT_BUTTON) == HIGH;
  int buttonPress =
    (left && right) ? DIR_UP :
    left ? DIR_LEFT :
    right ? DIR_RIGHT : buttonDirection;
  unsigned long now = millis();
  if (lastButtonPress == buttonPress) {
    if (now - lastButtonTime > 100 && buttonDirection != buttonPress) {
      buttonDirection = buttonPress;
      Serial.print("new buttonDirection=");
      Serial.println(directionStrings[buttonDirection]);
    }
  } else {
    lastButtonPress = buttonPress;
    lastButtonTime = now;
    Serial.print("new buttonPress=");
    Serial.println(directionStrings[lastButtonPress]);
  }
  interrupts();
  
  Discodelic1.refresh();
}


bool animate() {
  if (snake.dead) {
    if (millis() - snake.deadTime > 5000) {
      reset();
    }
    return false;
  }

  drawField();

  // blink the food.
  if ((millis() / 250) % 2 == 0) {
    food.draw(colorField);
  } else {
    food.draw(colorFood);
  }

  if (millis() > nextMoveTime) {

    // indexed by snake.direction, buttonDirection
    int newDirectionTable[4][4] = {
    // button:
    //  DIR_UP,    **, DIR_LEFT,  DIR_RIGHT
      { DIR_UP,    -1, DIR_LEFT,  DIR_RIGHT }, // snake.direction DIR_UP
      { DIR_DOWN,  -1, DIR_RIGHT, DIR_LEFT },  // snake.direction DIR_DOWN
      { DIR_LEFT,  -1, DIR_DOWN,  DIR_UP },    // snake.direction DIR_LEFT
      { DIR_RIGHT, -1, DIR_UP,    DIR_DOWN }   // snake.direction DIR_RIGHT
    };
    int direction = newDirectionTable[snake.direction][buttonDirection];

    FieldLoc nextLoc;
    bool dead = snake.body[snake.head].move(direction, nextLoc);

    if (dead) {
      Serial.print("Snake would be dead because can't move from ");
      snake.body[snake.head].print();
      Serial.print(" in direction ");
      Serial.println(directionStrings[direction]);
    } else {
      snake.direction = direction;
      buttonDirection = DIR_UP;
    }

    if (!snake.dead) {
      // Look for body collision.
      for (int bodyNdx = snake.tail; bodyNdx != snake.head; bodyNdx = (bodyNdx + 1) % worldSize) {
        if (snake.body[bodyNdx] == nextLoc) {
          snake.kill();
          Serial.println("DEAD by self bite");
          Serial.print("nextLoc=");
          nextLoc.print();
          Serial.println();
          snake.print();
          break;
        }
      }
    }

    if (!snake.dead) {
      // Actually make the move now.
      snake.move();

      // If the snake ate the food, put some more out.
      if (snake.body[snake.head] == food) {
        // Try each location starting at a random location. Make sure it
        // doesn't land in the body of the snake.
        FieldLoc startLoc = FieldLoc::randomLoc();
        uint8_t x, y;
        uint8_t panel = startLoc.panel;
        bool found = false;
        do {
          x = startLoc.x;
          do {
            y = startLoc.y;
            do {
              if (!(skipNdx(x) && skipNdx(y))) {
                // Legal location.
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
          Serial.println("Snake dead because nowhere to put food!");
          snake.print();
          snake.kill();
        }
      }
    }

    // Minimum 200 at length 60
    float length = snake.length(); 
    nextMoveTime = millis() + (length > 20 ? 200 : 600 - (400 * (length / 20)));
  }

  snake.draw();
  return false;
}

