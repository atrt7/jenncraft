#ifndef DRAWING_H
#define DRAWING_H

#include <fxcg/display.h>

extern color_t* vramadress;

void initDrawing(void);

void putPixel(int x, int y, color_t color);

void drawLine(int x1, int y1, int x2, int y2, color_t color);

#endif
