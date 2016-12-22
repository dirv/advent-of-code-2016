#include "stdio.h"
#include "stdbool.h"

typedef struct disc {
  int positions;
  int start;
} disc;

const int NUM_DISCS = 7;

disc discs[NUM_DISCS] = {
  { 17, 5 },
  { 19, 8 },
  { 7, 1 },
  { 13, 7 },
  { 5, 1 },
  { 3, 0 },
  { 11, 0 }
};

int main(int argc, char** argv) {

  int t = 0;
  while(true) {
    bool found = true;
    for(int d = 0; d < NUM_DISCS; ++d) {
      int pos = discs[d].start + t + d + 1;
      if ((pos % discs[d].positions) != 0) {
        found = false;
      }
    }
    if(found) break;
    t++;
  }
  printf("%d\n", t);
}
