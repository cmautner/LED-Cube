#include <TimerOne.h>
#include <DiscodelicLib.h>

  // Change every second
const long updateFrequency = 150 * 1000l;
bool doOnceInAnimate = true;
int loopIterator = 0;

#define Foreground (RGB2color(MAX_BRIGHT / 2, 0, 0))
#define Background (RGB2color(0, MAX_BRIGHT / 2, MAX_BRIGHT / 3))

bool animate(void);

int characterPosition = 0;
const char *helloWorld = "Hello World!";
int16_t helloWorldWidth;

void setup() {
  Serial.begin(115200);

  Discodelic1.setup();
//  Discodelic1.dumpAllPanels();

  Pixel pixel(0, 0, MAX_BRIGHT);

  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    DiscodelicGfx1.setGfxPanel(panelId);
    DiscodelicGfx1.fillScreen(Background);
//    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(0)->setLed(0, 0xffff);
//    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(7)->setLed(7, pixel);
  }
  Discodelic1.swapBuffers(true);
  for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
    DiscodelicGfx1.setGfxPanel(panelId);
    DiscodelicGfx1.fillScreen(Background);
//    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(0)->setLed(0, 0xffff);
//    Discodelic1.getPanel(FRAME_NEXT, panelId)->getRow(7)->setLed(7, pixel);
  }
  DiscodelicGfx1.setTextColor(Foreground, Background);
  DiscodelicGfx1.setTextSize(1);
  DiscodelicGfx1.setTextWrap(false);

  int16_t x, y;
  uint16_t w, h;
  DiscodelicGfx1.getTextBounds((char *)helloWorld, 0, 0, &x, &y, &w, &h);
  helloWorldWidth = w;
  Serial.print("helloWorldWidth=");
  Serial.println(helloWorldWidth);

  Discodelic::registerCallback(updateFrequency, animate);
}

void loop() {
  Discodelic1.refresh();
}


int slowCount;

bool animate() {
  
  if (digitalRead(SWITCH) == LOW) {
    if (slowCount < (1000000l / updateFrequency)) {
      slowCount++;
      return false;
    }
    slowCount = 0;

    char letter = helloWorld[characterPosition++];
    if (letter == 0) {
      characterPosition = 0;
      letter = helloWorld[characterPosition];
    }

    for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
      DiscodelicGfx1.setGfxPanel(panelId);
      DiscodelicGfx1.drawChar(0, 0, letter, Foreground, Background, 1);
    }
  } else {
    if (characterPosition-- <= (-1 * helloWorldWidth)) {
      characterPosition = 0;
    }
    for (PanelId panelId = PANEL_FIRST; panelId < NUM_PANELS; ++panelId) {
      DiscodelicGfx1.setGfxPanel(panelId);
      DiscodelicGfx1.setCursor(characterPosition, 0);
      DiscodelicGfx1.print(helloWorld);
    }
  }

  return true;
}

