#include "stdio.h"

int checkTriangle(int a, int b, int c) {
  if (a + b > c && a + c > b && b + c > a) {
    return 1;
  }
  return 0;
}

int collect(FILE *fp, int num, int* args) {
  int current = 0;
  int result;
  while(current < num && (result = fscanf(fp, "%d", &args[current])) != -1) {
    ++current;
  }
  return result;
}

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");

  int validCount = 0;
  int args[9];
  int result;
  while((result = collect(fp, 9, args)) != -1) {
    validCount += checkTriangle(args[0], args[3], args[6]);
    validCount += checkTriangle(args[1], args[4], args[7]);
    validCount += checkTriangle(args[2], args[5], args[8]);
  }

  printf("%d\n", validCount);
  fclose(fp);
}
