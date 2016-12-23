#include "stdio.h"
#include "stdbool.h"

long lows[5000];
long highs[5000];

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");
  int num = 0;
  while(fscanf(fp, "%ld-%ld",&lows[num], &highs[num]) > 0) {
    num++;
  }

  long curMin = 0;

  while(1){
    bool found = false;
    for(int i = 0; i < num; ++i) {
      if (lows[i] == curMin || (lows[i] < curMin && highs[i] > curMin)) {
        curMin = highs[i] + 1;
				found = true;
        break;
      }
    }
    if(!found)
      break;
  }
  printf("%ld\n", curMin);
}
