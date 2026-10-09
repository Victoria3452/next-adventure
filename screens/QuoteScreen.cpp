#include "Config.h"

struct Letter {
  char c;
  int x;
  int y;
};

Letter letters[100];
int letterCount;

void addLine(String text, int y)
{
  int charWidth = 12;

  int textWidth = text.length() * charWidth;
  int startX = (240 - textWidth) / 2;

  for (int i = 0; i < text.length(); i++)
  {
    letters[letterCount].c = text[i];
    letters[letterCount].x = startX + i * charWidth;
    letters[letterCount].y = y;

    letterCount++;
  }
}

void showQuote()
{
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  letterCount = 0;

  addLine("Always be YOURSELF", 20);
  addLine("unless you can be a", 55);

  int order[100];

  for (int i = 0; i < letterCount; i++)
  {
    order[i] = i;
  }

  // Fisher-Yates shuffle
  for (int i = letterCount - 1; i > 0; i--)
  {
    int j = random(i + 1);

    int temp = order[i];
    order[i] = order[j];
    order[j] = temp;
  }

  // Reveal letters in random order
  for (int k = 0; k < letterCount; k++)
  {
    int idx = order[k];

    tft.setCursor(
      letters[idx].x,
      letters[idx].y
    );

    tft.print(letters[idx].c);

    delay(120);
  }

  // Pause
  delay(1000);

  // Reveal dots one-by-one
  int dotY = 95;
  int dotSpacing = 12;

  int dot1x = 120 - dotSpacing;
  int dot2x = 120;
  int dot3x = 120 + dotSpacing;

  tft.setCursor(dot1x, dotY);
  tft.print(".");
  delay(400);

  tft.setCursor(dot2x, dotY);
  tft.print(".");
  delay(400);

  tft.setCursor(dot3x, dotY);
  tft.print(".");
  delay(1200);
}
