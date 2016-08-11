#include <TimerOne.h>
#include <DiscodelicLib.h>

  // Change every second
const long updateFrequency = 1000 * 1000l;
bool doOnceInAnimate = true;
int loopIterator = 0;

#define Foreground (RGB2color(MAX_BRIGHT, 0, 0))
#define Background (RGB2color(0, MAX_BRIGHT, MAX_BRIGHT/2))

void animate(void);

void setup() {
  Serial.begin(115200);

  Discodelic1.setup();
//  Discodelic1.dumpAllPanels();

  DiscodelicGfx discodelicGfx = Discodelic1.mDiscodelicGfx;
  Pixel pixel(0, 0, 3);

  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    discodelicGfx.setGfxPanel(panelId);
    discodelicGfx.fillScreen(Background);
    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(0)->setLed(0, 0xffff);
    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(7)->setLed(7, pixel);
  }
  Discodelic1.swapBuffers(true);
  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    discodelicGfx.setGfxPanel(panelId);
    discodelicGfx.fillScreen(Background);
    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(0)->setLed(0, 0xffff);
    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(7)->setLed(7, pixel);
  }
  Discodelic1.dumpAllPanels();
    Serial.println(Discodelic1.getPanel(FRAME_CURRENT, PANEL_FRONT)->isOrientedUp());
    Serial.println(Discodelic1.getPanel(FRAME_CURRENT, PANEL_FRONT)->getRow(0)->isOrientedUp());
  
  Timer1.initialize(updateFrequency);
  Timer1.attachInterrupt(animate);
}

void loop() {
  Discodelic1.refresh();
}

int characterPosition = 0;
const char *helloWorld = "Hello world!";

void animate() {
  if ((digitalRead(SWITCH) == LOW) && doOnceInAnimate) {
    Discodelic1.swapBuffers();
    doOnceInAnimate = false;
    return;
  }

  char letter = helloWorld[++characterPosition];
  if (letter == 0) {
    characterPosition = 0;
    letter = helloWorld[characterPosition];
  }

  DiscodelicGfx discodelicGfx = Discodelic1.mDiscodelicGfx;
  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    discodelicGfx.setGfxPanel(panelId);
    discodelicGfx.drawChar(0, 0, letter, Foreground, Background, 1);
  }

  Discodelic1.swapBuffers();
}

