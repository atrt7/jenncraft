#ifndef INPUT_H
#define INPUT_H

#include <fxcg/keyboard.h>

void keyupdate(void);

int keydownlast(int basic_keycode);

int keydownhold(int basic_keycode);

#endif
