#include "Animate.h"
#include "LED_board.h"

uint8_t frameCount;

void animate() {
  if (switchBuffers) {
    Serial.println("Missed realtime constraint");
    return;
  }
  // Every nth time through update.
  if (++frameCount < 10) {
    return;
  }
  frameCount = 0;
  
//  long thisMicros = micros();
//  Serial.println(thisMicros - lastMicros);
//  lastMicros = thisMicros;
  Pixel nextColor;
  Pixel prevColor;

  Panel *prevPanel = &panels[loopFrameNdx][PANEL_TOP];
  Panel *nextPanel = &panels[animateFrameNdx][PANEL_TOP];

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

  nextColor.red = random() & DIM_MASK;
  nextColor.green = random() & DIM_MASK;
  nextColor.blue = random() & DIM_MASK;
  for (int rowNdx = 3; rowNdx <= 4; ++rowNdx) {
    Vector *pNextRow = nextPanel->getRow(rowNdx);
    for (int ledNdx = 3; ledNdx <= 4; ++ledNdx) {
      pNextRow->setLed(ledNdx, nextColor);
    }
  }

  for (int panelNdx = PANEL_FIRST; panelNdx < NUM_PANELS; ++panelNdx) {
    if (panelNdx == PANEL_TOP) {
      // Done above, skip
      continue;
    }

    prevPanel = &panels[loopFrameNdx][panelNdx];
    nextPanel = &panels[animateFrameNdx][panelNdx];

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

  switchBuffers = true;
}

