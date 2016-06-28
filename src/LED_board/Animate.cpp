#include "Animate.h"
#include "DiscodelicLib.h"

uint8_t frameCount;
const int updateFrequency = 6;

int randomNearColor(int oldColor) {
  switch (oldColor) {
    case 0:
      // limit to (0, 1)
      return oldColor + random(0, 2);
    case DIM_MASK:
      // limit to (DIM_MASK-1, DIM_MASK)
      return oldColor + random(-1, 1);
    default:
      // limit to (oldColor-1, oldColor+1)
      return oldColor + random(-1, 2);
  }
}

void animate() {
  // Every nth time through update.
  if ((++frameCount % updateFrequency) != 0) {
    return;
  }

//  long thisMicros = micros();
//  Serial.println(thisMicros - lastMicros);
//  lastMicros = thisMicros;
  Pixel nextColor;
  Pixel prevColor;

  Panel *prevPanel = Discodelic1.getPanel(FRAME_CURRENT, PANEL_TOP);
  Panel *nextPanel = Discodelic1.getPanel(FRAME_NEXT, PANEL_TOP);

  Pixel prevOuterTopColor;
  prevPanel->getRow(0)->getLed(0, prevOuterTopColor);

  // Next outer ring = previous ring just inside it.
  for (int ringNdx = 0; ringNdx < 3; ++ringNdx) {
    prevPanel->getRow(ringNdx + 1)->getLed(ringNdx + 1, prevColor);
    for (int rowNdx = ringNdx; rowNdx < NUM_ROWS - ringNdx; ++rowNdx) {
      Vector *pNextRow = nextPanel->getRow(rowNdx);
      if (rowNdx == ringNdx || rowNdx == NUM_ROWS - ringNdx - 1) {
        // Copy all the leds in this row
        for (int ledNdx = ringNdx; ledNdx < NUM_ROWS - ringNdx; ++ledNdx) {
          pNextRow->setLed(ledNdx, prevColor);
        }
      } else {
        // Just do first and last LED in the column equal to the row
        pNextRow->setLed(ringNdx, prevColor);
        pNextRow->setLed(NUM_ROWS - ringNdx - 1, prevColor);
      }
    }
  }

  if (digitalRead(SWITCH) == HIGH) {
    if (frameCount % (2 * updateFrequency) == 0) {
        nextColor.red = random() & DIM_MASK;
        nextColor.green = random() & DIM_MASK;
        nextColor.blue = random() & DIM_MASK;
      } else {
        nextColor = prevColor;
      }
  } else {
    if ((frameCount % (4 * updateFrequency)) == 0) {
      nextColor = prevColor;
      switch (random() % 3) {
        case 0:
          nextColor.red = randomNearColor(nextColor.red);
          break;
        case 1:
          nextColor.green = randomNearColor(nextColor.green);
          break;
        case 2:
          nextColor.blue = randomNearColor(nextColor.blue);
          break;
        }
    } else {
      nextColor = prevColor;
    }
  }

  for (int rowNdx = 3; rowNdx <= 4; ++rowNdx) {
    Vector *pNextRow = nextPanel->getRow(rowNdx);
    for (int ledNdx = 3; ledNdx <= 4; ++ledNdx) {
      pNextRow->setLed(ledNdx, nextColor);
    }
  }

  for (PanelId panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
    if (panelNdx == PANEL_TOP) {
      // Done above, skip
      continue;
    }

    prevPanel = Discodelic1.getPanel(FRAME_CURRENT, panelNdx);
    nextPanel = Discodelic1.getPanel(FRAME_NEXT, panelNdx);

    for (int rowNdx = 0; rowNdx < NUM_ROWS; ++rowNdx) {
      Vector *pNextRow = nextPanel->getRow(rowNdx);
      if (rowNdx == 0) {
        nextColor = prevOuterTopColor;
      } else {
        prevPanel->getRow(rowNdx - 1)->getLed(0, nextColor);
      }
      for (int ledNdx = 0; ledNdx < NUM_LEDS; ++ledNdx) {
        pNextRow->setLed(ledNdx, nextColor);
      }
    }
  }

  Discodelic1.swapBuffers();
}

