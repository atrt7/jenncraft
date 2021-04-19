#include "util.h"

static const long SHAMT = sizeof(long) / 2;

int iabs(int i) {
  return (i < 0) ? -i : i;
} 

int signum(int i) {
  if (i > 0) {
    return 1;
  } else if (i < 0) {
    return -1;
  } else {
    return 0;
  }
}

long fxMul(long a, long b) {
  return ((long long)a * (long long)b) / (1 << SHAMT);
}

long fxDiv(long a, long b) {
  return ((long long)a * (1 << SHAMT)) / b;
}

long intToFx(int i) {
  return i * (1 << SHAMT);
}

int fxToInt(long l) {
  return l / (1 << SHAMT);
}
