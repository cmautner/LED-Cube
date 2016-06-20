#include <TimerOne.h>
#include "Panel.h"
#include "Refresh.h"
#include "LED_board.h"

//#define DEBUG

Panel panels[NUM_BUFFERS][NUM_PANELS];
volatile uint8_t loopFrameNdx;
volatile uint8_t timerFrameNdx;

const unsigned long frameTimeMillis = 1000;
unsigned long nextFrameTime;

const uint8_t DDRC_INIT = 0x37; // PC0-2, 4-5 as outputs. All others as inputs
const uint8_t DDRB_INIT = 0x23; // PB0-1,5 as outputs. All others as inputs
const int BLANK_ = 8;  // Enable for LEDs, active low
const int LATCH = 9;

const char * pingPongStrings[] = {
  "PING",
  "PONG"
};

const char * panelStrings[] = {
  "PANEL_BACK",
  "PANEL_TOP",
  "PANEL_LEFT",
  "PANEL_FRONT",
  "PANEL_RIGHT"
};

void dumpPanel(int panelNdx, int frameNdx = 0) {
  Pixel pixel;
  Serial.print("dumpPanel [");
  Serial.print(pingPongStrings[frameNdx]);
  Serial.print("][");
  Serial.print(panelStrings[panelNdx]);
  Serial.println("]");
  Panel *nextPanel = &panels[frameNdx][panelNdx];
  for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
    Vector *pNextRow = nextPanel->getRow(rowNdx);
//    Serial.println((int)pNextRow, HEX);
    for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
      pNextRow->getLed(ledNdx, pixel);
      pixel.print();
    }
    Serial.println();
  }
}

void dumpAllPanels() {
  for (int frameNdx = 0; frameNdx < NUM_BUFFERS; ++frameNdx) {
    for (int panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
      dumpPanel(panelNdx, frameNdx);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Set the pin directions for ports C (SCL, SDA, row select) and B (BLANK_, LAT)
  DDRC = DDRC_INIT;
  DDRB = DDRB_INIT;

  Pixel pixel;
  for (int frameNdx = 0; frameNdx < NUM_BUFFERS; ++frameNdx) {
    panels[frameNdx][PANEL_TOP].setOrientation(UP);
    panels[frameNdx][PANEL_BACK].setOrientation(DOWN);
    panels[frameNdx][PANEL_LEFT].setOrientation(DOWN);
    panels[frameNdx][PANEL_FRONT].setOrientation(UP);
    panels[frameNdx][PANEL_RIGHT].setOrientation(DOWN);
    for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
      for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
        Vector *pVector = panels[frameNdx][panelNdx].getRow(rowNdx);
        for (int pixelNdx = 0; pixelNdx < NUM_LEDS; ++pixelNdx) {
          // PANEL_BACK yellow, PANEL_TOP red, PANEL_LEFT green, PANEL_FRONT blue, PANEL_RIGHT purple
          pixel.red = (panelNdx == PANEL_TOP || panelNdx == PANEL_BACK || panelNdx == PANEL_RIGHT) ? DIM_MASK : 0;
          pixel.green = (panelNdx == PANEL_LEFT || panelNdx == PANEL_BACK) ? DIM_MASK : 0;
          pixel.blue = (panelNdx == PANEL_FRONT || panelNdx == PANEL_RIGHT) ? DIM_MASK : 0;
//          pixel.red = 0xf;
//          pixel.green = 0xf;
//          pixel.blue = 0xf;
          pVector->setLed(pixelNdx, pixel);
//        Serial.print("x=");
//        Serial.print(x);
//        Serial.print(", y=");
//        Serial.print(y);
//        Serial.print(", RGB=");
//        Serial.print(pixel.red, HEX);
//        Serial.print(":");
//        Serial.print(pixel.green, HEX);
//        Serial.print(":");
//        Serial.println(pixel.   blue, HEX);
        }
      }
    }
  }

  for (int panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
    for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
      for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
        if (((rowNdx == 0) && (ledNdx == 0)) || ((rowNdx == 7) && (ledNdx == 7))) {
          Vector *pVector = panels[PONG][panelNdx].getRow(rowNdx);
          Pixel pixel(rand(), rand(), rand());
          pVector->setLed(ledNdx, pixel);
        }
      }
    }
  }
  
  dumpAllPanels();

  timerFrameNdx = PONG;
  loopFrameNdx = 0;

  digitalWrite(SCL, HIGH);
  digitalWrite(BLANK_, LOW);

//  Timer1.initialize(1000);
//  Timer1.attachInterrupt(timerInterrupt);
}

unsigned long lastTime = 0;
unsigned long thisTime = 0;

void loop() {
  refresh();
}

#if 0
void loop() {
  // put your main code here, to run repeatedly:
  if (millis() >= nextFrameTime) {
#ifdef DEBUG
    Serial.println(".");
#endif
    Pixel nextColor;
    Pixel prevColor;

    Panel *prevPanel = &panels[timerFrameNdx][PANEL_TOP];
    Panel *nextPanel = &panels[loopFrameNdx][PANEL_TOP];

    Pixel prevOuterTopColor;
    prevPanel->getRow(0)->getLed(0, prevOuterTopColor);

    // Next outer ring = previous ring just inside it.
    for (int ringNdx = 0; ringNdx < 3; ++ringNdx) {
      prevPanel->getRow(ringNdx + 1)->getLed(ringNdx + 1, prevColor);
      for (int rowNdx = ringNdx; rowNdx < NUM_ROWS - ringNdx; ++rowNdx) {
        Vector *pNextRow = nextPanel->getRow(rowNdx);
#ifdef DEBUG
        Serial.print((int)pNextRow, HEX);
#endif
        if (rowNdx == ringNdx || rowNdx == NUM_ROWS - ringNdx - 1) {
          // Copy all the leds in this row
          for (int ledNdx = ringNdx; ledNdx < NUM_ROWS - ringNdx; ++ledNdx) {
            pNextRow->setLed(ledNdx, prevColor);
#ifdef DEBUG
            Serial.print(", ");
            Serial.print(ledNdx);
#endif            
          }
        } else {
          // Just do first and last LED in the column equal to the row
          pNextRow->setLed(ringNdx, prevColor);
#ifdef DEBUG
            Serial.print(", ");
            Serial.print(ringNdx);
#endif
          pNextRow->setLed(NUM_ROWS - ringNdx - 1, prevColor);
#ifdef DEBUG
            Serial.print(", ");
            Serial.print(NUM_ROWS - ringNdx - 1);
#endif
        }
#ifdef DEBUG
        prevColor.print(" ");
        Serial.println();
#endif
      }
    }

    nextColor.red = random() % 2 ? 0xf : 0;
    nextColor.green = random() % 2 ? 0xf : 0;
    nextColor.blue = random() % 2 ? 0xf : 0;
    for (int rowNdx = 3; rowNdx <= 4; ++rowNdx) {
      Vector *pNextRow = nextPanel->getRow(rowNdx);
#ifdef DEBUG
      Serial.print((int)pNextRow, HEX);
#endif
      for (int ledNdx = 3; ledNdx <= 4; ++ledNdx) {
        pNextRow->setLed(ledNdx, nextColor);
#ifdef DEBUG
        Serial.print(", ");
        Serial.print(ledNdx);
#endif            
      }
#ifdef DEBUG
      nextColor.print(" ");
      Serial.println();
#endif
    }

#ifdef DEBUG
    dumpPanel(PANEL_TOP);
#endif
    for (int panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
      if (panelNdx == PANEL_TOP) {
        // Done above, skip
        continue;
      }

      prevPanel = &panels[timerFrameNdx][panelNdx];
      nextPanel = &panels[loopFrameNdx][panelNdx];

      for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
        Vector *pNextRow = nextPanel->getRow(rowNdx);
        if (rowNdx == 0) {
          nextColor = prevOuterTopColor;
        } else {
          prevPanel->getRow(rowNdx - 1)->getLed(0, nextColor);
        }
        for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
          pNextRow->setLed(ledNdx, nextColor);
        }
      }
#ifdef DEBUG
      dumpPanel(PANEL_TOP);
      dumpPanel(panelNdx);
#endif
    }

    int tmpNdx = timerFrameNdx;
    loopFrameNdx = timerFrameNdx;
    timerFrameNdx = tmpNdx;

    nextFrameTime = millis() + frameTimeMillis;
  }
}
#endif
