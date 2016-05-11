#ifndef LED_BOARD_H
#define LED_BOARD_H

#include "Panel.h"

extern const int BLANK_;  // Enable for LEDs, active low
extern const int LATCH;

// In order from last shift register (first data shifted in) to first.
enum PanelId { 
  PANEL_BACK = 0,
  PANEL_TOP,
  PANEL_LEFT,
  PANEL_FRONT,
  PANEL_RIGHT,
  NUM_PANELS
};

extern Panel panels[2][NUM_PANELS];
extern uint8_t loopFrameNdx;
extern uint8_t timerFrameNdx;
extern volatile uint8_t nextFrameNdx;

#endif //LED_BOARD_H
