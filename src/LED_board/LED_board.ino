#include <TimerOne.h>
#include <DiscodelicLib.h>
#include "Animate.h"

void setup() {
  Serial.begin(115200);

  randomSeed(analogRead(0));

  Discodelic1.setup();
  Discodelic1.dumpAllPanels();

  // 40 msec close to 24 frames/sec
  Timer1.initialize(40000);
  Timer1.attachInterrupt(animate);
}

void loop() {
  Discodelic1.refresh();
}

