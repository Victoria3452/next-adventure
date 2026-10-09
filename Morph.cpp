#include "Config.h"
#include "Morph.h"

void drawPointCloud(
    const Point* points,
    int count
)
{
    tft.fillScreen(TFT_BLACK);

    for(int i = 0; i < count; i++)
    {
        tft.drawPixel(
            points[i].x,
            points[i].y,
            TFT_WHITE
        );
    }
}

void morphPoints(
    const Point* startPoints,
    const Point* endPoints,
    int count
)
{
    const int frames = 60;

    for(int frame = 0; frame <= frames; frame++)
    {
        float t = (float)frame / frames;

        tft.fillScreen(TFT_BLACK);

        for(int i = 0; i < count; i++)
        {
            int x =
                startPoints[i].x +
                t * (
                    endPoints[i].x -
                    startPoints[i].x
                );

            int y =
                startPoints[i].y +
                t * (
                    endPoints[i].y -
                    startPoints[i].y
                );

            tft.drawPixel(
                x,
                y,
                TFT_WHITE
            );
        }

        delay(16);
    }
}

void dispersePoints(
    const Point* points,
    int count
)
{
    static int dx[2000];
    static int dy[2000];

    for(int i = 0; i < count; i++)
    {
        dx[i] = random(-120,120);
        dy[i] = random(-70,70);
    }

    for(int frame = 0; frame < 40; frame++)
    {
        float t = frame / 40.0f;

        tft.fillScreen(TFT_BLACK);

        for(int i = 0; i < count; i++)
        {
            int x = points[i].x + dx[i] * t;
            int y = points[i].y + dy[i] * t;

            if(
                x >= 0 &&
                x < 240 &&
                y >= 0 &&
                y < 135
            )
            {
                tft.drawPixel(
                    x,
                    y,
                    TFT_WHITE
                );
            }
        }

        delay(20);
    }

    tft.fillScreen(TFT_BLACK);

    delay(100);
}

void fadePoints(
    const Point* points,
    int count
)
{
    const int frames = 40;

    for(int frame = 0; frame < frames; frame++)
    {
        tft.fillScreen(TFT_BLACK);

        float keep =
            1.0f -
            (float)frame / frames;

        int visible =
            count * keep;

        for(int i = 0; i < visible; i++)
        {
            tft.drawPixel(
                points[i].x,
                points[i].y,
                TFT_WHITE
            );
        }

        delay(25);
    }

    tft.fillScreen(TFT_BLACK);

    delay(500);
}
