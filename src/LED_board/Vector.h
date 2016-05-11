#ifndef VECTOR_H
#define VECTOR_H

#include "Pixel.h"

const uint8_t NUM_LEDS = 8;
enum Orientation { UP, DOWN };

class Vector {
  public:
    Vector() { }
    Pixel pixels[NUM_LEDS];

  private:
    Orientation m_orientation;
};
/*
class Column : public Vector {
  public:
    Column(Orientation orientation, Vector left, Vector right) : Vector(orientation),
      m_left(left), m_right(right) {
      
    }

  private:
    Vector m_left, m_right;
    ColorVector[3] leds;
}

class Row : public Vector {
  public:
    Row(Orientation orientation, Vector above, Vector below) : Vector(orientation),
      m_above(above), m_below(below) {
      
    }

  private:
    Vector m_above, m_below;
    struct {
      uint8_t led0 : 4, led1 : 4, led2 : 4, led3 : 4, led4 : 4, led5 : 4, led6 : 4, led7 : 4;
    } leds[
}
}
*/

#endif // VECTOR_H
