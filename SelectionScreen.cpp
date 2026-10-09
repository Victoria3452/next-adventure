#include "Config.h"

String options[5] = {
  "A) Bearcat!",
  "B) Dragon!",
  "C) Pegasus!",
  "D) Lion!"
};

int showSelectionScreen()
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);

  int y[4] = {15, 40, 65, 90};

  for(int i=0;i<4;i++)
  {
    tft.drawString(options[i], 30, y[i], 2);
  }

  int selected = random(4);

  for(int i=0;i<20;i++)
  {
    int current = random(4);

    tft.drawRect(
      20,
      y[current],
      160,
      26,
      TFT_WHITE
    );

    delay(100);

    tft.drawRect(
      20,
      y[current],
      160,
      26,
      TFT_BLACK
    );
  }

  tft.drawRect(
    20,
    y[selected],
    160,
    26,
    TFT_WHITE
  );

  delay(2000);

  return selected;
}