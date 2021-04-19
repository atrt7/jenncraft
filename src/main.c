#include "input.h"
#include "drawing.h"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>

int main(void) {
    int key;
    //int x1 = 50, y1 = 50, x2 = 0, y2 = 0;
    //int previousTicks = RTC_GetTicks();
	//float deltaTime;
    triangle tri = {
        {20, 20},
        {100, 20},
        {100, 100}
    };
    initDrawing();
    Bdisp_EnableColor(1);
    
    while(1) {
        keyupdate();
        if(keydownlast(KEY_PRGM_MENU)) {
            GetKey(&key);
        } else {
            //add code for updating
            /*int ticks = RTC_GetTicks();
			deltaTime = ticks-previousTicks;
			previousTicks = ticks;
			deltaTime /= 128.f;
			if(deltaTime > 0.1f) deltaTime = 0.1f;
            
            float ySpeed = (keydownlast(KEY_PRGM_DOWN)-keydownlast(KEY_PRGM_UP)) *144*deltaTime;
			float xSpeed = (keydownlast(KEY_PRGM_RIGHT)-keydownlast(KEY_PRGM_LEFT)) *144*deltaTime;*/
            
            if(keydownlast(KEY_PRGM_1)) {
                tri.one.x += 1;
                tri.one.y += 1;
            } else if(keydownlast(KEY_PRGM_2)) {
                tri.two.x += 1;
                tri.two.y += 1;
            } else if(keydownlast(KEY_PRGM_3)) {
                tri.three.x += 1;
                tri.three.y += 1;
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
            
            rasterize(tri, COLOR_GREENYELLOW);
            
            DrawFrame(0x0021);
			Bdisp_PutDisp_DD();
        }
    }
} 
