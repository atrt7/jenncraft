#include "drawing.h"
#include "util.h"
#include "fixed.h"

#include <fxcg/display.h>
//#include <math.h>

color_t* vramadress;

void initDrawing(void) {
	vramadress = (color_t*)GetVRAMAddress();
}

void DmaWaitNext(void){
	while(1){
		if((*DMA0_DMAOR)&4)//Address error has occurred stop looping
			break;
		if((*DMA0_CHCR_0)&2)//Transfer is done
			break;
	}
	SYNCO();
	*DMA0_CHCR_0&=~1;
	*DMA0_DMAOR=0;
}
void DoDMAlcdNonblockStrip(unsigned y1,unsigned y2){
	Bdisp_WriteDDRegister3_bit7(1);
	Bdisp_DefineDMARange(6,389,y1,y2);
	Bdisp_DDRegisterSelect(LCD_GRAM);

	*MSTPCR0&=~(1<<21);//Clear bit 21
	*DMA0_CHCR_0&=~1;//Disable DMA on channel 0
	*DMA0_DMAOR=0;//Disable all DMA
	*DMA0_SAR_0=((unsigned int)vramadress+(y1*384*2))&0x1FFFFFFF;//Source address is VRAM
	*DMA0_DAR_0=LCD_BASE&0x1FFFFFFF;//Destination is LCD
	*DMA0_TCR_0=((y2-y1+1)*384)/16;//Transfer count bytes/32
	*DMA0_CHCR_0=0x00101400;
	*DMA0_DMAOR|=1;//Enable DMA on all channels
	*DMA0_DMAOR&=~6;//Clear flags
	*DMA0_CHCR_0|=1;//Enable channel0 DMA
}
void DoDMAlcdNonblock(void){
	DoDMAlcdNonblockStrip(0,215);
}

void swapVec2(Vec2 *a, Vec2 *b) {
    Vec2 temp = *a;
    *a = *b;
    *b = temp;
}

int isVec2OutsideOfScreen(Vec2 v) {
  return (v.x <= 0 || v.x > LCD_WIDTH_PX || v.y <= 0 || v.y > LCD_HEIGHT_PX);
}

void putPixel(int x, int y, color_t color) {
    if(x < LCD_WIDTH_PX && x >= 0 && y < LCD_HEIGHT_PX && y >= 0) {
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

void drawWireFrameTriangle(triangle tri, color_t color) {
    drawLine(tri.one.x, tri.one.y, tri.two.x, tri.two.y, color);
    drawLine(tri.two.x, tri.two.y, tri.three.x, tri.three.y, color);
    drawLine(tri.three.x, tri.three.y, tri.one.x, tri.one.y, color);
}

void sortCoordsAscendingByY(triangle *tri) {
  Vec2 tmp;

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

void fillFlatSideTriangleInt(Vec2 v1, Vec2 v2, Vec2 v3, color_t outlineColor, color_t fillColor) {
    Vec2 vTmp1 = {v1.x, v1.y};
    Vec2 vTmp2 = {v1.x, v1.y};
    
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
        
        /*if (vTmp1.x == vTmp2.x) {
            for (int y = min(vTmp1.y, vTmp2.y); y <= max(vTmp1.y, vTmp2.y); ++y) {
                *(vramadress + (LCD_WIDTH_PX * y) + vTmp1.x) = color;
            }
        } else if (vTmp1.y == vTmp2.y) {
            for (int x = min(vTmp1.x, vTmp2.x); x <= max(vTmp1.x, vTmp2.x); ++x) {
                *(vramadress + (LCD_WIDTH_PX * vTmp1.y) + x) = color;
            }
        }*/
        
        /*if (vTmp1.x == vTmp2.x) {
            for (int y = min(vTmp1.y, vTmp2.y); y <= max(vTmp1.y, vTmp2.y); ++y) {
                putPixel(vTmp1.x, y, fillColor);
            }
        } else if (vTmp1.y == vTmp2.y) {
            for (int x = min(vTmp1.x, vTmp2.x); x <= max(vTmp1.x, vTmp2.x); ++x) {
                putPixel(x, vTmp1.y, fillColor);
            }
        }*/
        
        if (vTmp1.x == vTmp2.x) {
            int yMax = max(vTmp1.y, vTmp2.y);
            int yMin = min(vTmp1.y, vTmp2.y);
            for (int y = yMin; y <= yMax; ++y) {
                putPixel(vTmp1.x, y, fillColor);
            }
        } else if (vTmp1.y == vTmp2.y) {
            int xMin = min(vTmp1.x, vTmp2.x);
            int xMax = max(vTmp1.x, vTmp2.x);
            for (int x = xMin; x <= xMax; ++x) {
                putPixel(x, vTmp1.y, fillColor);
            }
        }
        
        /*if (vTmp1.x == vTmp2.x) {
            int y1 = min(vTmp1.y, vTmp2.y);
            int y2 = max(vTmp1.y, vTmp2.y);
            for (int y = y1; y <= y2; ++y) {
                putPixel(vTmp1.x, y, (y == y1 || y == y2) ? outlineColor : fillColor);
            }
        } else if (vTmp1.y == vTmp2.y) {
            int x1 = min(vTmp1.x, vTmp2.x);
            int x2 = max(vTmp1.x, vTmp2.x);
            for (int x = x1; x <= x2; ++x) {
                putPixel(x, vTmp1.y, (x == x1 || x == x2) ? outlineColor : fillColor);
            }
        }*/
        
        //drawLine(vTmp1.x, vTmp1.y, vTmp2.x, vTmp2.y, fillColor);
        
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
//     drawLine(v1.x, v1.y, v2.x, v2.y, outlineColor);
//     drawLine(v2.x, v2.y, v3.x, v3.y, outlineColor);
//     drawLine(v3.x, v3.y, v1.x, v1.y, outlineColor);
}

void rasterize(triangle tri, color_t outlineColor, color_t fillColor) {
  sortCoordsAscendingByY(&tri);

  if (tri.two.y == tri.three.y) {
    fillFlatSideTriangleInt(tri.one, tri.two, tri.three, outlineColor, fillColor);
    drawWireFrameTriangle(tri, outlineColor);
  } else if (tri.one.y == tri.two.y) {
    fillFlatSideTriangleInt(tri.three, tri.one, tri.two, outlineColor, fillColor);
    drawWireFrameTriangle(tri, outlineColor);
  } else {
    Vec2 tmp;
    tmp.x = fixtoi(itofix(tri.one.x) + fmul(fdiv(itofix(tri.two.y - tri.one.y), itofix(tri.three.y - tri.one.y)), itofix(tri.three.x - tri.one.x)));
    tmp.y = tri.two.y;
    fillFlatSideTriangleInt(tri.one, tri.two, tmp, outlineColor, fillColor);
    fillFlatSideTriangleInt(tri.three, tri.two, tmp, outlineColor, fillColor);
    drawWireFrameTriangle(tri, outlineColor);
    drawLine(tri.two.x, tri.two.y, tmp.x, tmp.y, outlineColor);
  }
}

Vec2 viewportToCanvas(int x, int y, int viewportWidth, int viewportHeight) {
    return (Vec2) {.x = x * LCD_WIDTH_PX/viewportWidth, .y =  y * LCD_HEIGHT_PX/viewportHeight};
}

Vec2 projectVertex(Vec3 v, int d) {
    return viewportToCanvas(v.x * d / v.z, v.y * d / v.z, 100, 100);
}

