#include "Config.h"

#include "MascotScreen.h"
#include "Morph.h"

#include "BearcatPoints.h"
#include "DragonPoints.h"
#include "PegasusPoints.h"
#include "LionPoints.h"

const int POINT_COUNT = 2000;

const Point* getPoints(int mascot)
{
    switch(mascot)
    {
        case BEARCAT:
            return bearcatPoints;

        case DRAGON:
            return dragonPoints;

        case PEGASUS:
            return pegasusPoints;

        case LION:
            return lionPoints;
    }

    return bearcatPoints;
}

void cycleMascots(int selected)
{
    int count;

    // Determine how many mascots to display
    // Each mascot morphs through all previous
    // school identities leading up to it
    switch(selected)
    {
        case BEARCAT:
            count = 1;
            break;

        case DRAGON:
            count = 2;
            break;

        case PEGASUS:
            count = 3;
            break;

        case LION:
            count = 4;
            break;

        default:
            count = 1;
    }

    int order[4];

    int index = 0;

    // Build the sequence of mascots to display,
    // starting with the selected identity and
    // continuing through its predecessors

    for(int mascot = selected;
        mascot >= BEARCAT;
        mascot--)
    {
        order[index++] = mascot;
    }

    // Display selected mascot
    drawPointCloud(
        getPoints(order[0]),
        POINT_COUNT
    );

    delay(2500);

    // Morph through previous mascot identities
    for(int i = 0; i < count - 1; i++)
    {
        morphPoints(
            getPoints(order[i]),
            getPoints(order[i + 1]),
            POINT_COUNT
        );

        delay(1500);
    }

    fadePoints(
        getPoints(order[count - 1]),
        POINT_COUNT
    );
}
