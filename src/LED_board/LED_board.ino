#include <TimerOne.h>
#include "Panel.h"

// Precondition: SCL is LOW
// Postcondition: SCL is LOW
#define CLOCK_DATA(a) { \
    digitalWrite(SDA, (a)); \
    /*Serial.println((a), HEX);*/ \
    digitalWrite(SCL, HIGH); \
    digitalWrite(SCL, LOW); \
}

Panel panels[2][NUM_PANELS];
uint8_t loopFrameNdx;
uint8_t timerFrameNdx;
volatile uint8_t nextFrameNdx;

uint8_t refreshNdx;
uint8_t rowNdx;


void setup() {
  Serial.begin(9600);
  
  DDRC = DDRC_INIT;
  DDRB = DDRB_INIT;

  Pixel pixel;

  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    for (int x = 0; x < NUM_LEDS; ++x) {
      for (int y = 0; y < NUM_ROWS; ++y) {
        switch (x) {
          case 0:
            pixel.red = 256 / (y + 1) - 1;
            pixel.green = pixel.blue = 0;
            break;
          case 1:
            pixel.green = 256 / (((y + 4) & 7) + 1) - 1;
            pixel.red = pixel.blue = 0;
            break;
          case 2:
            pixel.blue = 256 / (((NUM_ROWS - y) & 7) + 1) - 1;
            pixel.red = pixel.green = 0;
            break;
          case 3:
            pixel.red = 256 / (y + 1) - 1;
            pixel.green = 256 / (((y + 4) & 7) + 1) - 1; 
            pixel.blue = 256 / (((NUM_ROWS - y) & 7) + 1) - 1;
            break;
        }
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
        panels[0][panelNdx].setPixel(x, y, pixel);
        panels[1][panelNdx].setPixel(x, y, pixel);
      }
    }
  }

  Timer1.initialize(250);
  Timer1.attachInterrupt(timerInterrupt);
}

unsigned long lastTime = 0;
unsigned long thisTime = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if (loopFrameNdx != nextFrameNdx) {
    Pixel pixel;
    for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
      Panel &nextPanel = panels[nextFrameNdx][panelNdx];
      Panel &lastPanel = panels[loopFrameNdx][panelNdx];
      for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < NUM_ROWS; ++y) {
          switch (x) {
            case 0:
              lastPanel.getPixel(x, y, pixel);
              if (pixel.red > 0) {
                pixel.red--;
              }
              break;
            case 1:
              lastPanel.getPixel(x, y, pixel);
              if (pixel.green > 0) {
                pixel.green--;
              }
              break;
            case 2:
              lastPanel.getPixel(x, y, pixel);
              if (pixel.blue > 0) {
                pixel.blue--;
              }
              break;
            case 3:
              lastPanel.getPixel(x, y, pixel);
              pixel.red += 16;
              pixel.green += 16;
              pixel.blue += 16;
              break;
          }
          nextPanel.setPixel(x, y, pixel);
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
    
    if (loopFrameNdx == nextFrameNdx) {
      Timer1.stop();
      Serial.println("Missed real time constraint");
      while(1)
        ;
    }

    loopFrameNdx = nextFrameNdx;
  }
}

void timerInterrupt(void) {
  // Clock out one entire row
  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel &panel = panels[timerFrameNdx][panelNdx];
    // Clock out the row starting at the far end
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel pixel;
      panel.getPixel(ledNdx, rowNdx, pixel);
      CLOCK_DATA(pixel.green > 0 && pixel.green >> 4 >= refreshNdx);
    }
  }
  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel &panel = panels[timerFrameNdx][panelNdx];
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel pixel;
      panel.getPixel(ledNdx, rowNdx, pixel);
      CLOCK_DATA(pixel.red > 0 && pixel.red >> 4 >= refreshNdx);
    }
  }
  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel &panel = panels[timerFrameNdx][panelNdx];
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel pixel;
      panel.getPixel(ledNdx, rowNdx, pixel);
      CLOCK_DATA(pixel.blue > 0 && pixel.blue >> 4 >= refreshNdx);
    }
  }
  digitalWrite(BLANK_, HIGH);
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  PORTC = (PORTC & 0xF8) | rowNdx;
//  Serial.print("rowNdx:");
//  Serial.print(rowNdx);
//  Serial.print(", PORTC:");
//  Serial.println(PORTC, HEX);
  digitalWrite(BLANK_, LOW);

  if (++rowNdx >= NUM_ROWS) {
    rowNdx = 0;
//    if (++refreshNdx >= NUM_REFRESHES) {
//      refreshNdx = 0;
//      nextFrameNdx = timerFrameNdx;
//      timerFrameNdx = ++timerFrameNdx % 2;
//    }
  }
}

