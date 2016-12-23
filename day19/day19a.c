#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

const int NUM_ELVES = 3014603;


int findNext(bool *presents, int current) {
  for(int i = 0; i < NUM_ELVES; ++i) {
    int elf =(i+current)%NUM_ELVES;
    if(presents[elf])
      return elf;
  }
}

int main(int argc, char **argv) {
  int elvesLeft = NUM_ELVES;
  bool *presents = malloc(sizeof(bool)*NUM_ELVES);

  for(int i = 0; i < NUM_ELVES; ++i) {
    presents[i] = true;
  }

  long cur = 0;
  while(elvesLeft > 1) {
    int elf = cur % NUM_ELVES;
    if(presents[elf]) {
      int nextElf = findNext(presents, elf+1);
      presents[nextElf] = false;
      elvesLeft--;
    }
    cur++;
  }

  int elf = findNext(presents, 0);
  printf("%d\n", elf + 1);
  return 0;
}
