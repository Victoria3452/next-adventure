#ifndef MORPH_H
#define MORPH_H

#include "Point.h"

void drawPointCloud(
    const Point* points,
    int count
);

void morphPoints(
    const Point* startPoints,
    const Point* endPoints,
    int count
);

void dispersePoints(
    const Point* points,
    int count
);

void fadePoints(
    const Point* points,
    int count
);

#endif