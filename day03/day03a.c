#include "stdio.h"

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");

  int validCount = 0;
  int a, b, c;
  int result;
  while((result = fscanf(fp, "%d %d %d\n", &a, &b, &c)) != -1) {
    if (a + b > c && a + c > b && b + c > a) {
      validCount++;
    }
  }

  printf("%d\n", validCount);
  fclose(fp);
}
