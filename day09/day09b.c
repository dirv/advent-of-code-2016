#include "stdio.h"
#include "ctype.h"
#include <sys/stat.h>


FILE *fp;

void readCommand(int *numChars, int *numRepetitions) {
  fscanf(fp, "%dx%d)", numChars, numRepetitions);
}

long long countSection(int length) {
  long long curLength = 0;
  int ch;
  int curPos = ftell(fp);
  int lastPos = curPos + length;
  while(curPos < lastPos && ((ch = fgetc(fp)) != -1)) {
    if(ch == '(') {
      int numChars;
      int numRepetitions;
      readCommand(&numChars, &numRepetitions);
      curLength += numRepetitions * countSection(numChars);
    } else {
      if(!isspace(ch)) {
        curLength++;
      }
    }
    curPos = ftell(fp);
	}
  return curLength;
}

int main(int argc, char** argv) {
  fp = fopen("input.txt", "r");

  int fd = fileno(fp);
  struct stat buf;
  fstat(fd, &buf);

  printf("%lld\n", countSection(buf.st_size));
  return 0;
}
