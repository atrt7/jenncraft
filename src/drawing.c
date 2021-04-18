#include "drawing.h"

#include <fxcg/display.h>

color_t* vramadress;

void initDrawing(void) {
	vramadress = (color_t*)GetVRAMAddress();
}

void putPixel(int x, int y, color_t color) {
    if(x <= LCD_WIDTH_PX && x >= 0 && y <= LCD_HEIGHT_PX && y >= 0) {
        *(vramadress + (LCD_WIDTH_PX * y) + x) = color;
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
