#include "Panel.h"

void Panel::getPixel(int x, int y, Pixel &pixel) {
  pixel.red = array[y][x][RED_INDEX];
  pixel.green = array[y][x][GREEN_INDEX];
  pixel.blue = array[y][x][BLUE_INDEX];
}

void Panel::setPixel(int x, int y, Pixel &pixel) {
  uint8_t *color = array[y][x];
  color[RED_INDEX] = pixel.red;
  color[GREEN_INDEX] = pixel.green;
  color[BLUE_INDEX] = pixel.blue;
}

