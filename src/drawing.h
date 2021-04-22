#ifndef DRAWING_H
#define DRAWING_H

#include <fxcg/display.h>
#include <fxcg/heap.h>
#include <math.h>

typedef struct {
    int x, y;
}Vec2;

typedef struct {
    int x, y, z;
}Vec3;

typedef struct {
    Vec2 one;
    Vec2 two;
    Vec2 three;
}triangle;

#define LCD_GRAM	0x202
#define LCD_BASE	0xB4000000
#define VRAM_ADDR	0xA8000000
#define SYNCO() __asm__ volatile("SYNCO\n\t":::"memory");
// Module Stop Register 0
#define MSTPCR0		(volatile unsigned*)0xA4150030
// DMA0 operation register
#define DMA0_DMAOR	(volatile unsigned short*)0xFE008060
#define DMA0_SAR_0	(volatile unsigned*)0xFE008020
#define DMA0_DAR_0	(volatile unsigned*)0xFE008024
#define DMA0_TCR_0	(volatile unsigned*)0xFE008028
#define DMA0_CHCR_0	(volatile unsigned*)0xFE00802C

extern color_t* vramadress;

void initDrawing(void);

void DmaWaitNext(void);

void DoDMAlcdNonblockStrip(unsigned y1,unsigned y2);

void DoDMAlcdNonblock(void);

void swapVec2(Vec2 *a, Vec2 *b);

int isVec2OutsideOfScreen(Vec2 v);

void putPixel(int x, int y, color_t color);

void interpolate(int *out, int i0, int d0, int i1, int d1);

void drawLine(int x1, int y1, int x2, int y2, color_t color);

void sortCoordsAscendingByY(triangle *tri);

void fillFlatSideTriangleInt(Vec2 v1, Vec2 v2, Vec2 v3, color_t outlineColor, color_t fillColor);

void rasterize(triangle tri, color_t outlineColor, color_t fillColor);

Vec2 viewportToCanvas(int x, int y, int viewportWidth, int viewportHeight);

Vec2 projectVertex(Vec3 v, int d);

#endif
