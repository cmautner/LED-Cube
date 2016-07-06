#include <TimerOne.h>
#include <DiscodelicLib.h>
#include "Panel.h"

uint8_t frameCount;
const int updateFrequency = 60;

void animate(void);

void setup() {
  Serial.begin(115200);

  Discodelic1.setup();
  Discodelic1.dumpAllPanels();

  // 40 msec close to 24 frames/sec
  Timer1.initialize(40000);
  Timer1.attachInterrupt(animate);
}

void loop() {
  Discodelic1.refresh();
}

void fill2x2(PanelId panelNdx, int rowNdx, int pixelNdx, Pixel &pixel) {
  Panel *pPanel = Discodelic1.getPanel(FRAME_NEXT, panelNdx);
  for (int tmpRowNdx = rowNdx; tmpRowNdx <= rowNdx + 1; ++tmpRowNdx) {
    Vector *pVector = pPanel->getRow(tmpRowNdx);
    for (int tmpPixelNdx = pixelNdx; tmpPixelNdx <= pixelNdx + 1; ++tmpPixelNdx) {
      pVector->setLed(tmpPixelNdx, pixel);
    }
  }
}

void threeColorPattern(PanelId panelNdx, bool invert, PixelColor horizontal, PixelColor vertical) {
  Pixel pixel;

  // Do the upper left 3x3 with pattern (shown with horizontal==BLUE, vertical==GREEN):
  // 111 112 113
  // 121 122 123
  // 131 132 133
  // Or inverse of that pattern:
  // 333 332 331
  // 323 322 321
  // 313 312 311

  if (invert) {
    pixel.set(MAX_BRIGHT, MAX_BRIGHT, MAX_BRIGHT);
  } else {
    pixel.set(1, 1, 1);
  }

  int dimValue;
  for (int rowNdx = 0, vertBrightness = 1; vertBrightness <= MAX_BRIGHT; ++vertBrightness, rowNdx += 2) {
    for (int pixelNdx = 0, horizBrightness = 1; horizBrightness <= MAX_BRIGHT; ++horizBrightness, pixelNdx += 2) {
      dimValue = invert ? NUM_DIM_LEVELS - horizBrightness : horizBrightness;
      switch (horizontal) {
        case RED: pixel.red = dimValue; break;
        case GREEN: pixel.green = dimValue; break;
        case BLUE: pixel.blue = dimValue; break;
        default: break;
      }
      dimValue = invert ? NUM_DIM_LEVELS - vertBrightness : vertBrightness;
      switch (vertical) {
        case RED: pixel.red = dimValue; break;
        case GREEN: pixel.green = dimValue; break;
        case BLUE: pixel.blue = dimValue; break;
        default: break;
      }
      fill2x2(panelNdx, rowNdx, pixelNdx, pixel);
    }
  }

  // Fill in outer rows (shown with horizontal==BLUE, vertical==GREEN):
  //             211
  //             221
  //             231
  // 211 212 213 222

  pixel.set(2, 2, 2);

  // Right hand column first
  dimValue = invert ? MAX_BRIGHT: 1;
  switch (horizontal) {
    case RED: pixel.red = dimValue; break;
    case GREEN: pixel.green = dimValue; break;
    case BLUE: pixel.blue = dimValue; break;
    default: break;
  }
  
  for (int pixelNdx = 6, rowNdx = 0, vertBrightness = 1; vertBrightness <= MAX_BRIGHT; ++vertBrightness, rowNdx += 2) {
    dimValue = invert ? NUM_DIM_LEVELS - vertBrightness : vertBrightness;
    switch (vertical) {
      case RED: pixel.red = dimValue; break;
      case GREEN: pixel.green = dimValue; break;
      case BLUE: pixel.blue = dimValue; break;
      default: break;
    }
    fill2x2(panelNdx, rowNdx, pixelNdx, pixel);
  }

  // Bottom row second
  dimValue = invert ? MAX_BRIGHT: 1;
  switch (vertical) {
    case RED: pixel.red = dimValue; break;
    case GREEN: pixel.green = dimValue; break;
    case BLUE: pixel.blue = dimValue; break;
    default: break;
  }
  
  for (int rowNdx = 6, pixelNdx = 0, horizBrightness = 1; horizBrightness <= MAX_BRIGHT; ++horizBrightness, pixelNdx += 2) {
    dimValue = invert ? NUM_DIM_LEVELS - horizBrightness : horizBrightness;
    switch (horizontal) {
      case RED: pixel.red = dimValue; break;
      case GREEN: pixel.green = dimValue; break;
      case BLUE: pixel.blue = dimValue; break;
      default: break;
    }
    fill2x2(panelNdx, rowNdx, pixelNdx, pixel);
  }

  // Bottom right corner
  int rowNdx = 6, pixelNdx = 6;
  pixel.set(2, 2, 2);
  fill2x2(panelNdx, rowNdx, pixelNdx, pixel);
}

void twoColorPattern(PanelId panelNdx, PixelColor color1, PixelColor color2) {
  Pixel pixel;
  for (int rowNdx = 0, color1Brightness = 0; color1Brightness <= MAX_BRIGHT; ++color1Brightness, rowNdx +=2) {
    for (int pixelNdx = 0, color2Brightness = 0; color2Brightness <= MAX_BRIGHT; ++color2Brightness, pixelNdx += 2) {
      switch (color1) {
        case RED: pixel.red = color1Brightness; break;
        case GREEN: pixel.green = color1Brightness; break;
        case BLUE: pixel.blue = color1Brightness; break;
        default: break;
      }
      switch (color2) {
        case RED: pixel.red = color2Brightness; break;
        case GREEN: pixel.green = color2Brightness; break;
        case BLUE: pixel.blue = color2Brightness; break;
        default: break;
      }
      fill2x2(panelNdx, rowNdx, pixelNdx, pixel);
    }
  }
}

bool doOnce = true;
int startingPanel = PANEL_FIRST;
PixelColor first = RED;
PixelColor second = GREEN;
PixelColor third = BLUE;

void animate() {
  // Every nth time through update.
  if (digitalRead(SWITCH) == HIGH) {
    if ((++frameCount % updateFrequency) != 0) {
      return;
    }
  } else if (doOnce) {
    doOnce = false;
  } else {
    return;
  }

  int panelNdx = 0;
  twoColorPattern(static_cast<PanelId>((startingPanel + panelNdx++) % NUM_PANELS), first, second);
  twoColorPattern(static_cast<PanelId>((startingPanel + panelNdx++) % NUM_PANELS), second, third);
  twoColorPattern(static_cast<PanelId>((startingPanel + panelNdx++) % NUM_PANELS), third, first);
  threeColorPattern(static_cast<PanelId>((startingPanel + panelNdx++) % NUM_PANELS), false, first, second);
  threeColorPattern(static_cast<PanelId>((startingPanel + panelNdx++) % NUM_PANELS), true, first, second);

  Discodelic1.dumpAllPanels();

  ++startingPanel;
  PixelColor temp = first;
  first = second;
  second = third;
  third = temp;

  Discodelic1.swapBuffers();
}

