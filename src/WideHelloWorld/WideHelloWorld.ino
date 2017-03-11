#include <TimerOne.h>
#include <DiscodelicLib.h>

  // Change every second
const long updateFrequency = 150 * 1000l;
bool doOnceInAnimate = true;
int loopIterator = 0;

#define Foreground (RGB2color(MAX_BRIGHT / 2, 0, 0))
#define Background (RGB2color(0, MAX_BRIGHT / 2, MAX_BRIGHT / 3))

void animate(void);

int characterPosition = WIDE_PANEL_END;
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

  Timer1.initialize(updateFrequency);
  Timer1.attachInterrupt(animate);
}

void loop() {
  Discodelic1.refresh();
}


void animate() {
  if (digitalRead(SWITCH) == LOW) {
    char letter = helloWorld[++characterPosition];
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
      characterPosition = WIDE_PANEL_END;
    }


    DiscodelicGfx1.setWidePanelMode(true);
    DiscodelicGfx1.setCursor(characterPosition, 0);
    DiscodelicGfx1.print(helloWorld);

    DiscodelicGfx1.setWidePanelMode(false);
    Panel *pPanel = Discodelic1.getPanel(FRAME_NEXT, PANEL_TOP);
    Vector *pRow;
    Pixel pixel;
    for (int y = 0; y < NUM_LEDS; ++y) {
      pRow = pPanel->getRow(y);
      for (int x = 0; x < NUM_LEDS; ++x) {
        if (x == 0 || x == MAX_LED || y == 0 || y == MAX_LED) {
          Discodelic1.getTopPanelNeighborPixel(pixel, x, y);
          pRow->setLed(x, pixel);
        }
      }
    }
  }

  Discodelic1.swapBuffers();
}

