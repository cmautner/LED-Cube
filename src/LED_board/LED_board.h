#ifndef LED_BOARD_H
#define LED_BOARD_H

#include "Panel.h"

extern const int BLANK_;  // Enable for LEDs, active low
extern const int LATCH;

enum PingPongBuffers {
  PING = 0,
  PONG,
  NUM_BUFFERS
};

// In order from last shift register (first data shifted in) to first.
enum PanelId {
  PANEL_FIRST = 0,
  PANEL_BACK = 0,
  PANEL_TOP,
  PANEL_LEFT,
  PANEL_FRONT,
  PANEL_RIGHT,
  NUM_PANELS
};

extern Panel panels[NUM_BUFFERS][NUM_PANELS];
extern volatile uint8_t loopFrameNdx;
extern volatile uint8_t animateFrameNdx;
extern volatile bool switchBuffers;

#endif //LED_BOARD_H
