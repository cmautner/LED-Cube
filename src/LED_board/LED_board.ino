#include <TimerOne.h>
#include "Panel.h"
#include "TimerInterrupt.h"
#include "LED_board.h"

const uint8_t NUM_FRAMES = 2;

Panel panels[NUM_FRAMES][NUM_PANELS];
uint8_t loopFrameNdx = 0;
uint8_t timerFrameNdx = 0;
volatile uint8_t nextFrameNdx = 1;

const uint8_t DDRC_INIT = 0x37; // PC0-2, 4-5 as outputs. All others as inputs
const uint8_t DDRB_INIT = 0x23; // PB0-1,5 as outputs. All others as inputs
const int BLANK_ = 8;  // Enable for LEDs, active low
const int LATCH = 9;

void dumpPanel(int panelNdx) {
  Serial.print("dumpPanel [");
  Serial.print(nextFrameNdx);
  Serial.print("][");
  Serial.print(panelNdx);
  Serial.println("]");
  Panel &nextPanel = panels[nextFrameNdx][panelNdx];
  for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
    Vector &nextRow = nextPanel.getRow(rowNdx);
    for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
      Pixel &pixel = nextRow.pixels[ledNdx];
      Serial.print(pixel.green, HEX);
      Serial.print("-");
      Serial.print(pixel.red, HEX);
      Serial.print("-");
      Serial.print(pixel.blue, HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}

void setup() {
  Serial.begin(9600);

  // Set the pin directions for ports C (SCL, SDA, row select) and B (BLANK_, LAT)
  DDRC = DDRC_INIT;
  DDRB = DDRB_INIT;

  for (int frameNdx = 0; frameNdx < NUM_FRAMES; ++frameNdx) {
    panels[frameNdx][PANEL_TOP].setOrientation(UP);
    panels[frameNdx][PANEL_BACK].setOrientation(DOWN);
    panels[frameNdx][PANEL_LEFT].setOrientation(UP);
    panels[frameNdx][PANEL_FRONT].setOrientation(DOWN);
    panels[frameNdx][PANEL_RIGHT].setOrientation(DOWN);
    for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
      for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
        Vector &vector = panels[frameNdx][panelNdx].getRow(rowNdx);
        for (int pixelNdx = 0; pixelNdx < NUM_LEDS; ++pixelNdx) {
          Pixel &pixel = vector.pixels[pixelNdx];
          pixel.red = (panelNdx == 1 || panelNdx == 0 || panelNdx == 4) ? 0xf : 0;
          pixel.green = (panelNdx == 2 || panelNdx == 0) ? 0xf : 0;
          pixel.blue = (panelNdx == 3 || panelNdx == 4) ? 0xf : 0;
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

  digitalWrite(SCL, HIGH);
  digitalWrite(BLANK_, LOW);

  Timer1.initialize(250);
  Timer1.attachInterrupt(timerInterrupt);
}

unsigned long lastTime = 0;
unsigned long thisTime = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (loopFrameNdx != nextFrameNdx) {
    Panel &lastPanel = panels[loopFrameNdx][PANEL_TOP];
    Panel &nextPanel = panels[nextFrameNdx][PANEL_TOP];

    Pixel prevOuterTopColor = lastPanel.getRow(0).pixels[0];

    // Next outer ring = previous ring just inside it.
    for (int ringNdx = 0; ringNdx < 3; ++ringNdx) {
      Pixel &prevColor = lastPanel.getRow(ringNdx + 1).pixels[ringNdx + 1];
      for (int rowNdx = ringNdx; rowNdx < NUM_ROWS - ringNdx; ++rowNdx) {
        Vector &nextRow = nextPanel.getRow(rowNdx);
        if (rowNdx == ringNdx || rowNdx == NUM_ROWS - ringNdx - 1) {
          // Copy all the leds in this row
          for (int ledNdx = rowNdx; ledNdx < NUM_ROWS - rowNdx; ++ledNdx) {
            nextRow.pixels[ledNdx] = prevColor;
          }
        } else {
          // Just do first and last LED in the column equal to the row
          nextRow.pixels[rowNdx] = nextRow.pixels[NUM_ROWS - rowNdx - 1] = prevColor;
        }
      }
    }

    Pixel newColor;
    newColor.red = random();
    newColor.green = random();
    newColor.blue = random();
    for (int rowNdx = 3; rowNdx <= 4; ++rowNdx) {
      Vector &nextRow = nextPanel.getRow(rowNdx);
      nextRow.pixels[3] = nextRow.pixels[4] = newColor;
    }

    dumpPanel(PANEL_TOP);

    for (int panelNdx = PANEL_BACK; panelNdx < NUM_PANELS; ++panelNdx) {
      if (panelNdx == PANEL_TOP) {
        // Done above, skip
        continue;
      }

      lastPanel = panels[loopFrameNdx][panelNdx];
      nextPanel = panels[nextFrameNdx][panelNdx];

      for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
        Vector &nextRow = nextPanel.getRow(rowNdx);
        Pixel nextColor;
        if (rowNdx == 0) {
          nextColor = prevOuterTopColor;
        } else {
          nextColor = lastPanel.getRow(rowNdx - 1).pixels[0];
        }
        for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
          nextRow.pixels[ledNdx] = nextColor;
        }
      }
    }

    for (int panelNdx = PANEL_BACK; panelNdx < NUM_PANELS; ++panelNdx) {
      dumpPanel(panelNdx);
    }

    if (loopFrameNdx == nextFrameNdx) {
      Timer1.stop();
      Serial.println("Missed real time constraint");
      while(1)
        ;
    }

    loopFrameNdx = nextFrameNdx;

  }
}

