#ifndef DRAWING_H
#define DRAWING_H

#include "fixed.h"

#include <fxcg/display.h>
#include <fxcg/heap.h>
#include <math.h>

typedef struct {
    int x, y;
}vec2;

typedef struct {
    fix x, y, z;
}vec3;

typedef struct {
    vec2 one;
    vec2 two;
    vec2 three;
}triangle;

typedef struct {
    vec3 one;
    vec3 two;
    vec3 three;
}triangleVec3;

typedef struct {
    vec3 pos;
}camera;

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

#define HALF_LCD_WIDTH 192
#define HALF_LCD_HEIGHT 108

extern color_t* vramadress;

void initDrawing(void);

void DmaWaitNext(void);

void DoDMAlcdNonblockStrip(unsigned y1,unsigned y2);

void DoDMAlcdNonblock(void);

void swapVec2(vec2 *a, vec2 *b);

int isVec2OutsideOfScreen(vec2 v);

int isTriangleOutsideOfScreen(triangle tri);

void putPixel(int x, int y, color_t color);

void drawLine(int x1, int y1, int x2, int y2, color_t color);

vec2 projectVec3(vec3 vtx, camera cam);

void drawWireFrameTriangle(triangle tri, color_t color);

void drawWireframeTriangleVec3(triangleVec3 tri, color_t outlineColor, camera cam);

void triangleSortCoordsAscendingByY(triangle *tri);

void fillFlatSideTriangleInt(vec2 v1, vec2 v2, vec2 v3, color_t fillColor);

void rasterize(triangle tri, color_t outlineColor, color_t fillColor);

void rasterizeTriangleVec3(triangleVec3 tri, color_t outlineColor, color_t fillColor, camera cam);

#endif
