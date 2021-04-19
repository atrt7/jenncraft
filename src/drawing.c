#include "drawing.h"

#include <fxcg/display.h>
#include <fxcg/heap.h>
#include <math.h>

color_t* vramadress;

void initDrawing(void) {
	vramadress = (color_t*)GetVRAMAddress();
}

void swapCoordinates(coordinate *a, coordinate *b) {
    coordinate temp = *a;
    *a = *b;
    *b = temp;
}

void putPixel(int x, int y, color_t color) {
    if(x <= LCD_WIDTH_PX && x >= 0 && y <= LCD_HEIGHT_PX && y >= 0) {
        *(vramadress + (LCD_WIDTH_PX * y) + x) = color;
    }
}

void interpolate(int *out, int i0, int d0, int i1, int d1) {
    if(i0 == i1) {
        *out = d0;
    }
    float a = (float) (d1 - d0) / (float) (i1 - i0);
    float d = d0;
    for(int i = i0; i <= i0; i++) {
        out[i] = d;
        d += a;
    }
}

void drawLine(int x1, int y1, int x2, int y2, color_t color) {
    signed char ix;
    signed char iy;
 
    int delta_x = (x2 > x1?(ix = 1, x2 - x1):(ix = -1, x1 - x2)) << 1;
    int delta_y = (y2 > y1?(iy = 1, y2 - y1):(iy = -1, y1 - y2)) << 1;
 
   putPixel(x1, y1, color);
    if (delta_x >= delta_y) {
        int error = delta_y - (delta_x >> 1);
        while (x1 != x2) {
            if (error >= 0) {
                if (error || (ix > 0)) {
                    y1 += iy;
                    error -= delta_x;
                }
         }
            x1 += ix;
            error += delta_y;
            putPixel(x1, y1, color);
        }
    } else {
        int error = delta_x - (delta_y >> 1);
        while (y1 != y2) {
            if (error >= 0) {
                if (error || (iy > 0)) {
                    x1 += ix;
                    error -= delta_y;
                }
            }
            y1 += iy;
            error += delta_x;  
            putPixel(x1, y1, color);
        }
    }
}

void drawFilledTriangle(triangle *tri, color_t color) {
    
    if (tri->two.y < tri->one.y) { swapCoordinates(&(tri->two), &(tri->one)); }
    if (tri->three.y < tri->one.y) { swapCoordinates(&(tri->three), &(tri->one)); }
    if (tri->three.y < tri->two.y) { swapCoordinates(&(tri->three), &(tri->two)); }
    
}
