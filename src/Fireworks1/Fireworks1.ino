#include <DiscodelicLib.h>

const int bgRed = 0;
const int bgGreen = 0;
const int bgBlue = 0;

#define colorBackground (RGB2color(bgRed, bgGreen, bgBlue))

const long updatePeriod = 1 * 100000l;
const int minSize = 3;
const int maxSize = 10;
const int minLifetime = 3;
const int maxLifetime = 10;

class Firework {
  public:
    int centerX, centerY;
    int size;
    float age;
    int lifetime;
    uint8_t red, green, blue;
    Firework *next;
    Firework *prev;
    bool fill;
  
    Firework() {
      size = random(minSize, maxSize);
      lifetime = random(minLifetime, maxLifetime);
      age = 0;
      red = random(0, 4);
      green = random(0, 4);
      blue = random(0, 4);
      centerX = random(0, WIDE_PANEL_END);
      centerY = random(0, TALL_PANEL_END);
      fill = random(0,2);
      next = NULL;
      prev = NULL;
//      Serial.println("Created");
    }
  
    void draw() {
//      Serial.println("Drawing");
      int radius = size * age / (lifetime * 2);
      uint16_t color = RGB2color(red, green, blue);
//    DiscodelicGfx1.setTraceMode(true);
      if (fill) {
        DiscodelicGfx1.fillCircle(centerX, centerY, radius, color);
      } else {
        DiscodelicGfx1.drawCircle(centerX, centerY, radius, color);
      }
//    DiscodelicGfx1.setTraceMode(false);

//      float maturity = age / lifetime;
//      float vivacity = 1.0f - maturity;
//  
//      int fadeRed = red * vivacity + bgRed * maturity;
//      int fadeGreen = green * vivacity + bgGreen * maturity;
//      int fadeBlue = blue * vivacity + bgBlue * maturity;
//  
//      for (int i = 1; i <= size * maturity; ++i) {
//        float intensity = 1;
//        uint16_t color = RGB2color((int)(fadeRed * intensity), (int)(fadeGreen * intensity),
//          (int)(fadeBlue * intensity));
//        DiscodelicGfx1.enableTrace(true);
//        DiscodelicGfx1.drawCircle(centerX, centerY, i, color);
//        DiscodelicGfx1.setTraceMode(false);
//      }
    }

    void print() {
      Serial.print("x,y=");
      Serial.print(centerX);
      Serial.print(",");
      Serial.print(centerY);
      Serial.print(" sz=");
      Serial.print(size);
      Serial.print(" col=");
      Serial.print(red);
      Serial.print(",");
      Serial.print(green);
      Serial.print(",");
      Serial.print(blue);
      Serial.print(" lf=");
      Serial.print(lifetime);
      Serial.print(" age=");
      Serial.print(age);
      Serial.print(" prv");
      Serial.print((int)prev);
      Serial.print(" nxt");
      Serial.println((int)next);
    }
};
Firework *head = NULL;

void setup() {
  Serial.begin(115200);

  if (true || digitalRead(SWITCH) == HIGH) {
    long seed = 0;
    for (int i = 0; i < 10; ++i) {
      
      seed = (seed << 3) | (analogRead(A0) & 7);
      delay(1);
    }
    randomSeed(seed ^ micros());
  }

  Discodelic1.setup();
  DiscodelicGfx1.setWidePanelMode(true);
  DiscodelicGfx1.setTallPanelMode(true);
  DiscodelicGfx1.setWrapMode(true);
  Discodelic::registerCallback(updatePeriod, animate);
}

void loop() {
  Discodelic1.refresh();
}


bool animate() {
  DiscodelicGfx1.fillScreen(colorBackground);
 

  Firework *last = NULL;
  for (Firework *firework = head; firework != NULL; firework = firework->next) {
    firework->age++;
//    Serial.print((int)firework);
//    Serial.print(": ");
//    firework->print();
    firework->draw();
    if (firework->age == firework->lifetime) {
      if (firework->prev != NULL) {
        firework->prev->next = firework->next;
      } else {
        head = firework->next;
      }
      if (firework->next != NULL) {
        firework->next->prev = firework->prev;
      }
      free(firework);
    } else {
      last = firework;
    }
  }
  if (last == NULL) {
//    Serial.println("Creating head");
    head = new Firework();
  } else if (random(0, 5) == 1) {
//    Serial.println("Creating non head");
    last->next = new Firework();
    last->next->prev = last;
  }
  return true;
}

