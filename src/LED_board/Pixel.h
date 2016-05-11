#ifndef PIXEL_H
#define PIXEL_H

#include <avr/io.h>

class Pixel {
public:
  uint8_t red : 4, green : 4, blue : 4;
  Pixel & operator= (const Pixel & other) {
    if (this != &other) {
      red = other.red;
      green = other.green;
      blue = other.blue;
    }
    return *this;
  }
};

#endif // PIXEL_H
