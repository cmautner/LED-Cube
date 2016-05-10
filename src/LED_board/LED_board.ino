#include <TimerOne.h>
#include "Panel.h"

// Precondition: SCL is HIGH
// Postcondition: SCL is HIGH
#define CLOCK_DATA(a) { \
  if (a) { \
    PORTC = 0x10 | rowNdx; \
    PORTC = 0x30 | rowNdx; \
  } else { \
    PORTC = rowNdx; \
    PORTC = 0x20 | rowNdx; \
  } \
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
    Pixel pixel;
    for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
      Panel &nextPanel = panels[nextFrameNdx][panelNdx];
      Panel &lastPanel = panels[loopFrameNdx][panelNdx];
      for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < NUM_ROWS; ++y) {
          switch (x) {
            case 0:
              lastPanel.getPixel(x, y, pixel);
              pixel.red+=8;
              break;
            case 1:
              lastPanel.getPixel(x, y, pixel);
              pixel.green-=8;
              break;
            case 2:
              lastPanel.getPixel(x, y, pixel);
              pixel.blue+=8;
              break;
            case 3:
              lastPanel.getPixel(x, y, pixel);
              pixel.red += 8;
              pixel.green -= 8;
              pixel.blue += 8;
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


//           cycle
//val   0123 4567 89AB CDEF
//0000  0000 0000 0000 0000
//0001  1000 0000 0000 0000
//0010  1000 0000 1000 0000
//0011  1000 0010 0001 0000
//
//0100  1000 1000 1000 1000
//0101  1000 1001 0010 0100
//0110  1001 0010 1001 0010
//0111  1001 0101 0100 1010
//
//1000  0110 1010 1011 0101
//1001  0110 1101 0110 1101
//1010  0111 0110 1101 1011
//1011  0111 0111 0111 0111
//
//1100  0111 1101 1110 1111
//1101  0111 1111 0111 1111
//1110  0111 1111 1111 1111
//1111  1111 1111 1111 1111

const uint16_t cycleLookup[16] = {
  0x0000, 0x8000, 0x8080, 0x8210,
  0x8888, 0x8924, 0x9292, 0x954a,
  0x6ab5, 0x6d6d, 0x76db, 0x7777,
  0x7def, 0x7f7f, 0x7fff, 0xffff};

void timerInterrupt(void) {
  // Clock out one entire row
  const int cycleBit = 1 << refreshNdx;
  
  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel &panel = panels[timerFrameNdx][panelNdx];
    // Clock out the row starting at the far end
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel pixel;
      panel.getPixel(ledNdx, rowNdx, pixel);
//      Serial.print("px.grn=");
//      Serial.print(pixel.green >> 4, HEX);
//      Serial.print(", cycleBit=");
//      Serial.print(cycleBit, HEX);
//      Serial.print(", cycleLookup[]=");
//      Serial.print(cycleLookup[pixel.green >> 4], HEX);
//      Serial.print(", []|bit=");
//      Serial.println(cycleLookup[pixel.green >> 4] | cycleBit, HEX);      
      CLOCK_DATA(cycleLookup[pixel.green >> 4] & cycleBit);
    }
  }
  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel &panel = panels[timerFrameNdx][panelNdx];
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel pixel;
      panel.getPixel(ledNdx, rowNdx, pixel);
      CLOCK_DATA(cycleLookup[pixel.red >> 4] & cycleBit);
    }
  }
  for (int panelNdx = 0; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel &panel = panels[timerFrameNdx][panelNdx];
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel pixel;
      panel.getPixel(ledNdx, rowNdx, pixel);
      CLOCK_DATA(cycleLookup[pixel.blue >> 4] & cycleBit);
    }
  }
//  digitalWrite(BLANK_, HIGH);
  digitalWrite(SCL, LOW);
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
//  PORTC = (PORTC & 0xF8) | rowNdx;
//  Serial.print("rowNdx:");
//  Serial.print(rowNdx);
//  Serial.print(", PORTC:");
//  Serial.println(PORTC, HEX);
//  digitalWrite(BLANK_, LOW);

  PORTC = 0x20 | rowNdx;
  if (++rowNdx >= NUM_ROWS) {
    rowNdx = 0;
    if (++refreshNdx >= NUM_REFRESHES) {
      refreshNdx = 0;
      nextFrameNdx = timerFrameNdx;
      timerFrameNdx = ++timerFrameNdx % 2;
    }
  }
}

