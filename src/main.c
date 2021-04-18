#include "input.h"
#include "drawing.h"

#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <fxcg/rtc.h>

int main(void) {
    int key;
    int x1 = 50, y1 = 50, x2 = 0, y2 = 0;
    int previousTicks = RTC_GetTicks();
	float deltaTime;
    initDrawing();
    Bdisp_EnableColor(1);
    
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
            
            float ySpeed = (keydownlast(KEY_PRGM_DOWN)-keydownlast(KEY_PRGM_UP)) *144*deltaTime;
			float xSpeed = (keydownlast(KEY_PRGM_RIGHT)-keydownlast(KEY_PRGM_LEFT)) *144*deltaTime;
            
            x2 += xSpeed;
            y2 += ySpeed;
            
            Bdisp_AllClr_VRAM();
            
            //add drawing code
            
            drawLine(x1, y1, x2, y2, 0x0021);
            
            DrawFrame(0x0021);
			Bdisp_PutDisp_DD();
        }
    }
} 
