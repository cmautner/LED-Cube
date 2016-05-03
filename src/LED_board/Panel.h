#include "Pixel.h"
#include "LED_board.h"


class Panel {
  uint8_t array[NUM_ROWS][NUM_LEDS][NUM_COLORS];

public:
  void getPixel(int x, int y, Pixel &pixel);
  void setPixel(int x, int y, Pixel &pixel);
};

