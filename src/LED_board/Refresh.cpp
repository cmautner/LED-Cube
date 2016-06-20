#include <Arduino.h>
#include "Refresh.h"
#include "LED_board.h"

static uint8_t refreshNdx;
static uint8_t rowNdx;

#define NUM_REFRESHES (1 << NUM_DIM_BITS)

#if 0

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

const uint16_t dimmingSchedule[16] = {
  0x0000, 0x8000, 0x8080, 0x8210,
  0x8888, 0x8924, 0x9292, 0x954a,
  0x6ab5, 0x6d6d, 0x76db, 0x7777,
  0x7def, 0x7f7f, 0x7fff, 0xffff};
#else
//           cycle
//val   0123
//0000  0000
//0001  1000
//0010  1010
//0011  1111

const uint16_t dimmingSchedule[4] = {
  0x0, 0x8, 0xa, 0xf};
#endif
void refresh(void) {


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
  
  for (int panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
    Panel *panel = &panels[frameNdx][panelNdx];
    int orientedRowNdx = panel->isOrientedUp() ? rowNdx : NUM_ROWS - 1 - rowNdx;
    // Clock out the row starting at the far end
    Vector *pRow = panel->getShiftRow(orientedRowNdx);

    for (int color = FIRST_COLOR; color < NUM_COLORS; ++color) {
//      Serial.print("color=");
//      Serial.print(color);
//      Serial.print(" ");
      uint32_t leds = pRow->leds[color];
      for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx, leds >>=  NUM_DIM_BITS) {
        if (dimmingSchedule[leds & DIM_MASK] & cycleBit) {
        // clock is low, data is low
          PORTC |= 0x10;
        } else {
          PORTC &= ~0x10;
        }
        // clock
        PORTC |= 0x20;
        // return to low
        PORTC &= ~0x30;
      }
    }
  }
  digitalWrite(BLANK_, HIGH);
  PORTC = rowNdx;
  digitalWrite(LATCH, HIGH);
  digitalWrite(LATCH, LOW);
  digitalWrite(BLANK_, LOW);
//  digitalWrite(SCL, LOW);







//  PORTC = (PORTC & 0xF8) | rowNdx;
//  Serial.print("rowNdx:");
//  Serial.print(rowNdx);
//  Serial.print(", PORTC:");
//  Serial.println(PORTC, HEX);
//  digitalWrite(BLANK_, LOW);
}

