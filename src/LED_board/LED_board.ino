#include <TimerOne.h>
#include "Panel.h"
#include "Refresh.h"
#include "LED_board.h"
#include "Animate.h"

//#define DEBUG

Panel panels[NUM_BUFFERS][NUM_PANELS];
volatile uint8_t loopFrameNdx;
volatile uint8_t animateFrameNdx;
volatile bool switchBuffers = false;

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

  loopFrameNdx = PONG;
  animateFrameNdx = PING;

  digitalWrite(SCL, HIGH);
  digitalWrite(BLANK_, LOW);

  // 40 msec close to 24 frames/sec
  Timer1.initialize(40000);
  Timer1.attachInterrupt(animate);
}

unsigned long lastTime = 0;
unsigned long thisTime = 0;

void loop() {
  refresh();
}

