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

void swapCoordinates(coordinate *a, coordinate *b);

void putPixel(int x, int y, color_t color);

void interpolate(int *out, int i0, int d0, int i1, int d1);

void drawLine(int x1, int y1, int x2, int y2, color_t color);

void sortCoordsAscendingByY(triangle *tri);

void fillFlatSideTriangleInt(coordinate v1, coordinate v2, coordinate v3, color_t outlineColor, color_t fillColor);

void rasterize(triangle tri, color_t outlineColor, color_t fillColor);

#endif
