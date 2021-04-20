#include "util.h"

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

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}
