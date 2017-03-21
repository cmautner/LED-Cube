#include <DiscodelicLib.h>


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
const long updatePeriod = 75 * 1000l; // 10 Hz

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
} food;

class Snake {
  public:
    FieldLoc body[worldSize];
    uint8_t head = 0, tail = 0;
    int direction;
    bool dead = false;

  void move() {
    FieldLoc oldHead = body[head];
    FieldLoc newHead;

    // Make the move, but don't store the new location in the body.
    dead = oldHead.move(direction, newHead);
    if (dead) {
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
  for (FrameId frameId = FRAME_CURRENT; frameId <= FRAME_NEXT; ++frameId) {
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

void reset() {
  snake = Snake();
  FieldLoc snakeHead;
  snake.print();
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
}

void setup() {
  Serial.begin(115200);

  if (true || digitalRead(SWITCH) == HIGH) {
    long seed = 0;
    for (int i = 0; i < 10; ++i) {
      seed = (seed << 3) | (analogRead(0) & 7);
      delay(1);
    }
    randomSeed(seed ^ micros());
  }

  Discodelic1.setup();

  reset();

  Discodelic::registerCallback(updatePeriod, animate);
}

void loop() {
  // put your main code here, to run repeatedly:
  Discodelic1.refresh();
}

const int movePeriod = 4; // 1 second
int stepCount = 0;

bool animate() {
  ++stepCount;
  if ((digitalRead(SWITCH) == LOW) && snake.dead) {
    delay(1);
    if (stepCount == 60) {
      reset();
      stepCount = 0;
    }
    return false;
  }

  drawField();

  // blink the food.
  if (stepCount % 3 == 0) {
    food.draw(colorField);
  } else {
    food.draw(colorFood);
  }

  FieldLoc foodPeers[3];
  int numFoodPeers = food.getPeers(foodPeers);

  if ((stepCount == movePeriod) && !snake.dead) {
    stepCount = 0;

    // REMOVE when buttons
    FieldLoc headLoc = snake.body[snake.head];
    FieldLoc nextLoc;

    // Run through all of the directions and pick the best one.
    long closest = 1000000l;
    int bestDirection = -1;
    bool found = false;
    bool samePanelFound = false;
    for (int direction = DIR_UP; direction <= DIR_RIGHT; ++direction) {
      // Don't reverse course
      if ((snake.direction == DIR_UP && direction == DIR_DOWN) ||
        (snake.direction == DIR_DOWN && direction == DIR_UP) ||
        (snake.direction == DIR_LEFT && direction == DIR_RIGHT) ||
        (snake.direction == DIR_RIGHT && direction == DIR_LEFT)) {
        continue;
      }

      // Test the move
      if (headLoc.move(direction, nextLoc)) {
        // Dead move, try again.
        continue;
      }

      // Valid move, compare all its peers to the food.
      FieldLoc peers[3];
      int numPeers = nextLoc.getPeers(peers);
      for (int peersNdx = 0; peersNdx < numPeers; ++peersNdx) {
        nextLoc = peers[peersNdx];
        for (int foodPeersNdx = 0; foodPeersNdx < numFoodPeers; ++foodPeersNdx) {
          food = foodPeers[foodPeersNdx];
          if (nextLoc.panel == food.panel) {
            // Some peers are actually on the same panel. This is a good move.
            samePanelFound = true;
            long xDist = food.x - nextLoc.x;
            long yDist = food.y - nextLoc.y;
            long distance = (xDist * xDist) + (yDist * yDist);
            if (distance < closest) {
              closest = distance;
              bestDirection = direction;
            } else if (distance == closest && random(0, 2)) {
              // Equally as good as another, pick either at random.
              bestDirection = direction;
            }
          }
        }
      }

      if (!samePanelFound) {
        // All moves so far have resulted in a different panel than the food.
        if (bestDirection == -1) {
          // Nothing better so far, default to this direction. Hopefully we get
          // a smart move later to replace it.
          bestDirection = direction;
        }
        // If this is a legal move in the right direction to the food panel, use it.
        switch (nextLoc.panel) {
          case top:
            if ((food.panel == front && direction == DIR_DOWN) ||
              (food.panel == right && direction == DIR_RIGHT)) {
              bestDirection = direction;
            }
            break;
          case front:
            if ((food.panel == top && direction == DIR_UP) ||
              (food.panel == right && direction == DIR_RIGHT)) {
              bestDirection = direction;
            }
            break;
          case right:
            if ((food.panel == top && direction == DIR_UP) ||
              (food.panel == front && direction == DIR_LEFT)) {
              bestDirection = direction;
            }
            break;
        }
      }
    } // end loop through all directions

    if (bestDirection == -1) {
      snake.dead = true;
      Serial.println("DEAD by no direction found");
      snake.print();
    } else {
      snake.direction = bestDirection;
      // Look for body collision.
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
        found = false;
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
          snake.dead = true;
        }
      }
    }
  }

  snake.draw();
  return true;
}

