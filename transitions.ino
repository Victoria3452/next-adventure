#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#include "Config.h"
#include "QuoteScreen.h"
#include "SelectionScreen.h"
#include "MascotScreen.h"

void setup()
{
  tft.init();
  tft.setRotation(1);

  Serial.begin(115200);

  randomSeed(micros());
}

void loop()
{
  showQuote();

  int selected =
      showSelectionScreen();

  cycleMascots(selected);
}


