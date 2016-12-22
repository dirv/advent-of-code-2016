#include "stdio.h"
#include "stdbool.h"
#include "string.h"

char trapIdentifiers[4][3] = { "^^.", ".^^", "^..", "..^" };

bool isTrap(char *prev) {
  for(int i = 0; i < 4; ++i)
    if(strncmp(prev, trapIdentifiers[i], 3) == 0)
      return true;
  return false;
}

void calculateNextRow(char *in, char *out) {
  char prev[3];
  char *current = in;
  while(*(current+1) != '\0') {
    fflush(NULL);
    strncpy(prev, current - 1, 3);
    *out++ = isTrap(prev) ? '^' : '.';
    current++;
  }
}

int safeTiles(char *start, char *end) {
  int count = 0;
  char *current = start;
  while(current != end) {
    if(*current == '.')
      count++;
    current++;
  }
  return count;
}

int main(int argc, char **argv) {
  char startRow[150] = "..^^^.^.^^^.^.......^^.^^^^.^^^^..^^^^^.^.^^^..^^.^.^^..^.^..^^...^.^^.^^^...^^.^.^^^..^^^^.....^.....";
  char nextRow[150] = ".";
  strncpy(nextRow, startRow, 150);
  char *in = &startRow[1];
  char *out = &nextRow[1];
  int length = strlen(in) - 1;
  int totalTiles = safeTiles(in, in + length);
  for(int i = 1; i < 400000; ++i) {
    calculateNextRow(in, out);
    totalTiles += safeTiles(out, out + length);
    char *temp = out;
    out = in;
    in = temp;
  }
  printf("%d\n", totalTiles);
  return 0;
}
