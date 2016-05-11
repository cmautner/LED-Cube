#include <Arduino.h>
#include "TimerInterrupt.h"
#include "LED_board.h"


const uint8_t NUM_REFRESHES = 16;

static uint8_t refreshNdx;
static uint8_t rowNdx;

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
  
//  Serial.print("timerInterrupt timerFrameNdx ");
//  Serial.print(timerFrameNdx);
//  Serial.print(", refreshNdx ");
//  Serial.print(refreshNdx);
//  Serial.print(", row ");
//  Serial.println(rowNdx);
  for (int panelNdx = PANEL_BACK; panelNdx < NUM_PANELS; ++panelNdx) {
//    Serial.print("P");
//    Serial.print(panelNdx);
//    Serial.print(" ");
    Panel &panel = panels[timerFrameNdx][panelNdx];
    // Clock out the row starting at the far end
    Vector &row = panel.getRow(rowNdx);
    
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel &pixel = row.pixels[ledNdx];
      CLOCK_DATA(cycleLookup[pixel.green] & cycleBit);
    }
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel &pixel = row.pixels[ledNdx];
      CLOCK_DATA(cycleLookup[pixel.red] & cycleBit);
    }
    for (int ledNdx = NUM_LEDS - 1; ledNdx >= 0; --ledNdx) {
      Pixel &pixel = row.pixels[ledNdx];
      CLOCK_DATA(cycleLookup[pixel.blue] & cycleBit);
    }
//      Serial.print("px.grn=");
//      Serial.print(cycleLookup[pixel.green] & cycleBit, HEX);
//      Serial.print("-");
//      Serial.print(cycleLookup[pixel.red] & cycleBit, HEX);
//      Serial.print("-");
//      Serial.print(cycleLookup[pixel.blue] & cycleBit, HEX);
//      Serial.print(" ");
//    Serial.println();
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

