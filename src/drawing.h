#ifndef DRAWING_H
#define DRAWING_H

#include <fxcg/display.h>
#include <fxcg/heap.h>
#include <math.h>

typedef struct {
    int x, y;
}coordinate;

typedef struct {
    coordinate one;
    coordinate two;
    coordinate three;
}triangle;

extern color_t* vramadress;

void initDrawing(void);

void swapCoordinates(coordinate *a, coordinate *b);

void putPixel(int x, int y, color_t color);

void interpolate(int *out, int i0, int d0, int i1, int d1);

void drawLine(int x1, int y1, int x2, int y2, color_t color);

void drawFilledTriangle(triangle *tri, color_t color);

#endif
