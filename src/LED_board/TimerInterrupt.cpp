#include <Arduino.h>
#include "TimerInterrupt.h"
#include "LED_board.h"

extern void dumpAllPanels();
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
    Serial.println(a, HEX); \
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

  if (++rowNdx >= NUM_ROWS) {
    rowNdx = 0;
    if (++refreshNdx >= NUM_REFRESHES) {
#ifdef DEBUG
      Serial.print("!");
#endif
      refreshNdx = 0;
    }
  }

  uint8_t frameNdx = timerFrameNdx;
  // Clock out one entire row
  const int cycleBit = 1 << refreshNdx;
  
//  Serial.print("timerInterrupt timerFrameNdx ");
//  Serial.println(timerFrameNdx);
//  Serial.print(", refreshNdx ");
//  Serial.print(refreshNdx);
//  Serial.print(", row ");
//  Serial.println(rowNdx);
  for (int panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
//    Serial.print("P");
//    Serial.print(panelNdx);
//    Serial.print(" ");
    Panel *panel = &panels[frameNdx][panelNdx];
    // Clock out the row starting at the far end
    Vector *pRow = panel->getShiftRow(rowNdx);

    for (int color = FIRST_COLOR; color < NUM_COLORS; ++color) {
//      Serial.print("color=");
//      Serial.print(color);
//      Serial.print(" ");
      uint32_t leds = pRow->leds[color];
      if (panelNdx == PANEL_TOP) {
//        Serial.print(rowNdx);
//        Serial.print(" ");
//        Serial.print(leds, HEX);
//        Serial.println();
//          delayMicroseconds(250);
      }
      for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx, leds >>=  4) {
        if (!(cycleLookup[leds & 0xf] & cycleBit)) {
//        if (cycleLookup[leds & 0xf] != 0xffff) {
//        if ((leds & 0xf) != 0xf) {
          pRow->print();
          Serial.print(leds, HEX);
          Serial.print(", ");
          Serial.print(leds & 0xf, HEX);
          Serial.print(", ");
          Serial.println(cycleLookup[leds & 0xf], HEX);
        }
        int bit;
        if ((rowNdx == 0) && (ledNdx == 0) || (rowNdx == 7) && (ledNdx == 7)) {
           bit = (color ^ panelNdx) & 7 ? 0x10 : 0; 
        } else {
          bit = 1;
        }
        // clock is low, data is low
        if (bit) {
          PORTC |= 0x10;
        } else {
          PORTC &= ~0x10;
        }
        // clock
        PORTC |= 0x20;
        // return to low
        PORTC &= ~0x30;
//        CLOCK_DATA(cycleLookup[leds & 0xf] & cycleBit);
      }
    }
  }
  digitalWrite(BLANK_, HIGH);
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  PORTC = rowNdx;
  digitalWrite(BLANK_, LOW);
//  digitalWrite(SCL, LOW);







//  PORTC = (PORTC & 0xF8) | rowNdx;
//  Serial.print("rowNdx:");
//  Serial.print(rowNdx);
//  Serial.print(", PORTC:");
//  Serial.println(PORTC, HEX);
//  digitalWrite(BLANK_, LOW);
}

