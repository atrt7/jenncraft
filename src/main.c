#include "input.h"
#include "drawing.h"
#include "util.h"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>
#include <fxcg/misc.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    int key;
    int frames = 0;
    //int x1 = 50, y1 = 50, x2 = 0, y2 = 0;
    int previousTicks = RTC_GetTicks();
    int frameTicks = previousTicks;
	float deltaTime;
    unsigned char out[11];
    //sys_strcpy((char *) out, "  FPS:  ");
    
    camera cam = {
            {ftofix(0.0f), ftofix(0.0f), ftofix(5.0f)}
    };
    
    int modelNumTris = 12;
    triangleVec3 modelTris[] = {
            {
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(1.0f), ftofix(1.0f), ftofix(-1.0f) }
            },
            {
                    { ftofix(1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(1.0f) }
            },
            {
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(-1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(1.0f) }
            },
            {
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(-1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(-1.0f) }
            },
            {
                    { ftofix(1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(-1.0f) }
            },
            {
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(-1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(-1.0f) }
            },
            {
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(1.0f), ftofix(1.0f), ftofix(1.0f) }
            },
            {
                    { ftofix(1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(1.0f) }
            },
            {
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(-1.0f) }
            },
            {
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(1.0f) },
                    { ftofix(-1.0f), ftofix(-1.0f), ftofix(1.0f) }
            },
            {
                    { ftofix(1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(1.0f), ftofix(1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(1.0f) }
            },
            {
                    { ftofix(-1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(1.0f), ftofix(-1.0f) },
                    { ftofix(1.0f), ftofix(-1.0f), ftofix(-1.0f) }
            }
    };
    
    initDrawing();
    Bdisp_EnableColor(1);
    DrawFrame(0x0021);
    
    while(1) {
        keyupdate();
        if(keydownlast(KEY_PRGM_MENU)) {
            GetKey(&key);
        } else {
            
            //add code for updating
            int ticks = RTC_GetTicks();
			deltaTime = ticks-previousTicks;
			previousTicks = ticks;
			deltaTime /= 128.f;
			if(deltaTime > 0.1f) deltaTime = 0.1f;
            frames++;
            
            //fix ySpeed = ftofix((keydownlast(KEY_PRGM_DOWN)-keydownlast(KEY_PRGM_UP)) *144*deltaTime);
			//fix xSpeed = ftofix((keydownlast(KEY_PRGM_RIGHT)-keydownlast(KEY_PRGM_LEFT)) *144*deltaTime);
            
            fix ySpeed = ftofix(0.1f);
            fix xSpeed = ftofix(0.1f);
            fix zSpeed = ftofix(0.1f);
            
            if(keydownlast(KEY_PRGM_1)) {
                cam.pos.x += xSpeed;
            } else if(keydownlast(KEY_PRGM_2)) {
                cam.pos.y += ySpeed;
            } else if(keydownlast(KEY_PRGM_3)) {
                cam.pos.z += xSpeed;
            }
            
            /*if(keydownlast(KEY_PRGM_1)) {
                tri.one.x += xSpeed;
                tri.one.y += ySpeed;
                tri.two.x += xSpeed;
                tri.two.y += ySpeed;
                tri.three.x += xSpeed;
                tri.three.y += ySpeed;
            }*/
            
            //x2 += xSpeed;
            //y2 += ySpeed;
            
            Bdisp_AllClr_VRAM();
            //add drawing code
            
            
            /*drawLine(tri.one.x, tri.one.y, tri.two.x, tri.two.y, 0x0021);
            drawLine(tri.two.x, tri.two.y, tri.three.x, tri.three.y, 0x0021);
            drawLine(tri.three.x, tri.three.y, tri.one.x, tri.one.y, 0x0021);*/
            
            /*for(int i = 0; i <= 16; i++) {
                rasterize((triangle) {.one.x = i * 8 + tri.one.x, .one.y = i * 8 + tri.one.y, .two.x = i * 8 + tri.two.x, .two.y = i * 8 + tri.two.y, .three.x = i * 8 + tri.three.x, .three.y = i * 8 + tri.three.y}, 0x0021, COLOR_HOTPINK);
            }*/
            
            for(int i = 0; i < modelNumTris; i++) {
            drawWireframeTriangleVec3(modelTris[i], 0, cam);
            }
            
            //rasterizeCube();
            
            //rasterize(tri, 0x0021, COLOR_HOTPINK);
            
            if((ticks - frameTicks) / 128 >= 1) {
                unsigned char num[3];
                itoa(frames, num);
                strcpy((char *) out, "  FPS:");
                strcat((char *) out, (char *) num);
                frames = 0;
                frameTicks += 128;
            }
            PrintXY(3, 8, (char *) out, TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
            DoDMAlcdNonblock();
            DmaWaitNext();
        }
    }
} 
