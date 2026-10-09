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
  // Display opening quote animation
  showQuote();

  // Present mascot choices and randomly select one
  int selected =
      showSelectionScreen();

  // Display selected mascot and morph through previous mascot identities
  cycleMascots(selected);
}


