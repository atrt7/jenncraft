#include "drawing.h"
#include "util.h"

#include <fxcg/display.h>
//#include <math.h>

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

void sortCoordsAscendingByY(triangle *tri) {
  coordinate tmp;

  if (tri->one.y > tri->two.y) {
    tmp = tri->one;
    tri->one = tri->two;
    tri->two = tmp;
  }

  if (tri->one.y > tri->three.y) {
    tmp = tri->one;
    tri->one = tri->three;
    tri->three = tmp;
  }

  if (tri->two.y > tri->three.y) {
    tmp = tri->two;
    tri->two = tri->three;
    tri->three = tmp;
  }
}

void fillFlatSideTriangleInt(coordinate v1, coordinate v2, coordinate v3, color_t color) {
    coordinate vTmp1 = {v1.x, v1.y};
    coordinate vTmp2 = {v1.x, v1.y};
    
    int changed1 = 0;
    int changed2 = 0;
    
    int dx1 = iabs(v2.x - v1.x);
    int dy1 = iabs(v2.y - v1.y);
        
    int dx2 = iabs(v3.x - v1.x);
    int dy2 = iabs(v3.y - v1.y);
        
    int signx1 = signum(v2.x - v1.x);
    int signx2 = signum(v3.x - v1.x);
        
    int signy1 = signum(v2.y - v1.y);
    int signy2 = signum(v3.y - v1.y);
    
    if (dy1 > dx1) {
        int tmp = dx1;
        dx1 = dy1;
        dy1 = tmp;
        changed1 = 1;
    }
        
    if (dy2 > dx2) {
        int tmp = dx2;
        dx2 = dy2;
        dy2 = tmp;
        changed2 = 1;
    }
        
    int e1 = 2 * dy1 - dx1;
    int e2 = 2 * dy2 - dx2;
        
    for (int i = 0; i <= dx1; i++) {
        drawLine(vTmp1.x, vTmp1.y, vTmp2.x, vTmp2.y, 0x0021);
        
        while (e1 >= 0) {
            if (changed1)
                vTmp1.x += signx1;
            else
                vTmp1.y += signy1;
            e1 = e1 - 2 * dx1;
        }
        
        if (changed1)
            vTmp1.y += signy1;
        else
            vTmp1.x += signx1;  
        
        e1 = e1 + 2 * dy1;
        
        /* here we rendered the next point on line 1 so follow now line 2
            * until we are on the same y-value as line 1.
            */
        while (vTmp2.y != vTmp1.y) {
            while (e2 >= 0) {
                if (changed2)
                    vTmp2.x += signx2;
                else
                    vTmp2.y += signy2;
                e2 = e2 - 2 * dx2;
            }

            if (changed2)
                vTmp2.y += signy2;
            else
                vTmp2.x += signx2;

            e2 = e2 + 2 * dy2;
        }
    }
}

void rasterize(triangle tri, color_t color) {
  sortCoordsAscendingByY(&tri);

  if (tri.two.y == tri.three.y) {
    fillFlatSideTriangleInt(tri.one, tri.two, tri.three, color);
  } else if (tri.one.y == tri.two.y) {
    fillFlatSideTriangleInt(tri.three, tri.one, tri.two, color);
  } else {
    coordinate tmp;
    tmp.x = fxToInt(intToFx(tri.one.x) + fxMul(fxDiv(intToFx(tri.two.y - tri.one.y), intToFx(tri.three.y - tri.one.y)), intToFx(tri.three.x - tri.one.x)));
    tmp.y = tri.two.y;
    fillFlatSideTriangleInt(tri.one, tri.two, tmp, color);
    fillFlatSideTriangleInt(tri.three, tri.two, tmp, color);
  }
}
