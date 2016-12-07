#include "stdio.h"
#include "stdbool.h"
#include "string.h"

bool contains(char **l, char **lEnd, char *s) {
  while(l < lEnd) {
    if(strncmp(l, s, 2) == 0) {
      return true;
    }
    l++;
  }
  return false;
}

bool checkForReversals(char *a, char *aEnd, char **b, char **bEnd) {
  while(a < aEnd) {
    char reversal[2] = { *(a+1), *a };
    if(contains(b, bEnd, reversal)) {
      return true;
    }
    a++;
  }
  return false;
}

char** findAba(char *s, int length, char** abas) {
  for(int i = 0; i < length - 2; ++i) {
    if(s[i] != s[i+1]
        && s[i] == s[i+2]) {
      strncpy(abas++, &s[i], 2);
    }
  }
  return abas;
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
    char abas[50][3];
    char babs[50][3];
    char **curAbas = &abas[0];
    char **curBabs = &babs[0];
    while(position < end) {
      int nextBracket = inHypernet ? ']' : '[';

      char* stop = strchr(position, nextBracket);
      int length;
      if(stop != NULL) {
        length = stop - position;
      } else {
        length = strlen(position);
      }
      if(inHypernet) {
        curBabs = findAba(position, length, curBabs);
        inHypernet = false;
      } else {
        curAbas = findAba(position, length, curAbas);
        inHypernet = true;
      }

      position += length;
    }
    if (checkForReversals(abas, curAbas, babs, curBabs))
      totalFound++;
  }
  printf("%d\n", totalFound);
}
