#include "input.h"
#include <string.h>

const unsigned short* keyboard_register = (unsigned short*)0xA44B0000;
unsigned short lastkey[8];
unsigned short holdkey[8];
 
void keyupdate(void) {
	memcpy(holdkey, lastkey, sizeof(unsigned short)*8);
	memcpy(lastkey, keyboard_register, sizeof(unsigned short)*8);
}
int keydownlast(int basic_keycode) {
	int row, col, word, bit; 
	row = basic_keycode%10; 
	col = basic_keycode/10-1; 
	word = row>>1; 
	bit = col + 8*(row&1); 
	return (0 != (lastkey[word] & 1<<bit)); 
}
int keydownhold(int basic_keycode) {
	int row, col, word, bit; 
	row = basic_keycode%10; 
	col = basic_keycode/10-1; 
	word = row>>1; 
	bit = col + 8*(row&1); 
	return (0 != (holdkey[word] & 1<<bit)); 
}
