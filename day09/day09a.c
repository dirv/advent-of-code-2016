#include "stdio.h"
#include "ctype.h"

void readCommand(FILE *fp, int *numChars, int *numRepetitions) {
  fscanf(fp, "%dx%d)", numChars, numRepetitions);
}

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");

  int curLength = 0;
  int ch;
  while((ch = fgetc(fp)) != -1) {
    if(ch == '(') {
      int numChars;
      int numRepetitions;
      readCommand(fp, &numChars, &numRepetitions);
      for(int i = 0; i < numChars; ++i) {
        fgetc(fp);
      }
      curLength += numChars * numRepetitions;
    } else {
      if(!isspace(ch)) {
        curLength++;
      }
    }
  }
  printf("%d\n", curLength);
  return 0;
}
