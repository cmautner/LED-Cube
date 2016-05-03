#include <avr/io.h>

const uint8_t RED_INDEX = 0;
const uint8_t GREEN_INDEX = 1;
const uint8_t BLUE_INDEX = 2;
const uint8_t NUM_COLORS = 3; // 3 colors

class Pixel {
public:
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
};

