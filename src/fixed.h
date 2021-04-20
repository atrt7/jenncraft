#ifndef FIXED_H
#define FIXED_H

// Bit lenght of the decimal part, change it to change the precision :
#define DB 15


typedef int fix;


// Fixed dot manipulations functions and macros :
#define FIX(x) ((x)<<DB)

#define UNFIX(x) ((x)>>DB)

char* fixtostr (fix n, char* string);

fix ftofix(float f);
float fixtof(fix f);

fix itofix(int i);

int fixtoi(fix f);

fix fdiv(fix x, fix y);
fix fmul(fix x, fix y);

fix fsqrt(fix f);

fix fsin(fix a);
fix fcos(fix a);
fix ftan(fix a);


#endif // FIXED_H
