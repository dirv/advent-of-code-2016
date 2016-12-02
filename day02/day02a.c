#include "stdio.h"

int moves[9][4] = {
  {1, 4, 1, 2},
  {2, 5, 1, 3},
  {3, 6, 2, 3},
  {1, 7, 4, 5},
  {2, 8, 4, 6},
  {3, 9, 5, 6},
  {4, 7, 7, 8},
  {5, 8, 7, 9},
  {6, 9, 8, 9}
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
      printf("%d", position);
    } else {
      position = moves[position-1][moveIndex(c)];
    }
  }
  printf("\n");
  return 0;
}
