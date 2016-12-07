#include "stdio.h"
#include "stdbool.h"
#include "string.h"

bool findAbba(char *s, int length) {
  for(int i = 0; i < length - 3; ++i) {
    if(s[i] != s[i+1]
        && s[i] == s[i+3]
        && s[i+1] == s[i+2]) {
      return true;
    }
  }
  return false;
}

int main(int argc, char** argv) {

  FILE *fp = fopen("input.txt", "r");

  int result;
  int totalFound = 0;
  char ip[400];
  while((result = fscanf(fp, "%s\n", ip)) > 0) {
    char *end = ip + strlen(ip);
    bool inHypernet = false;
    char *position = ip;
    bool found = false;
    while(position < end) {
      int nextBracket = inHypernet ? ']' : '[';

      char* stop = strchr(position, nextBracket);
      int length;
      if(stop != NULL) {
        length = stop - position;
      } else {
        length = strlen(position);
      }
      if(findAbba(position, length)) {
        if(inHypernet) {
          found = false;
          break;
        }
        found = true;
      }

      position += length;

      if (inHypernet) {
        inHypernet = false;
      } else {
        inHypernet = true;
      }
    }
    if(found) {
      totalFound++;
    }

  }
  printf("%d\n", totalFound);
}
