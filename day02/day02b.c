#include "stdio.h"

int moves[14][4] = {
  {1, 3, 1, 1},
  {2, 6, 2, 3},
  {1, 7, 2, 4},
  {4, 8, 3, 4},
  {5, 5, 5, 6},
  {2, 10, 5, 7},
  {3, 11, 6, 8},
  {4, 12, 7, 9},
  {9, 9, 8, 9},
  {6, 10, 10, 11},
  {7, 13, 11, 12},
  {8, 12, 11, 12},
  {11, 13, 13, 13}
};

int moveIndex(int c) {
  switch(c) {
    case 'U':
      return 0;
    case 'D':
      return 1;
    case 'L':
      return 2;
    case 'R':
      return 3;
  }
  return -1;
}

int main(int argc, char** argv) {
  FILE *input = fopen("input.txt", "r");

  int position = 5;
  int c;
  while((c = fgetc(input)) != EOF) {
    if(c == '\n') {
      if(position > 9) {
        printf("%c", 'A' + position - 10);
      } else {
        printf("%d", position);
      }
    } else {
      position = moves[position-1][moveIndex(c)];
    }
  }
  printf("\n");
  return 0;
}
