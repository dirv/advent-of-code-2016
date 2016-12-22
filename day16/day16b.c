#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void strnrev(char *dest, char *src, int n) {
  char *c = src + n;
  while(c >= src) {
    *dest++ = *(--c);
  }
  *dest = 0;
}

void strswitch(char *s) {
  while(*s != 0) {
    if(*s == '1') {
      *s = '0';
    } else {
      *s = '1';
    }
    s++;
  }
}

// approach to take:
// do it in bits instead
const int requiredLength = 35651584;

int main(int argc, char **argv) {

  printf("%ld\n", sizeof(char));
  char *a = (char*)malloc(sizeof(char)*(requiredLength+1));
  char *b = (char*)malloc(sizeof(char)*(requiredLength+1));
  strcpy(a, "11100010111110100");

  int length = strlen(a);

  while(length < requiredLength) {
    strnrev(b, a, length);
    strswitch(b);
    strcat(a, "0");
    int maxChars = requiredLength - length - 1;
    strncat(a, b, maxChars);
    length *= 2;
    length++;
    printf("%d\n", length);
  }

  length = requiredLength;
  while(length % 2 == 0) {
    length /= 2;
    for(int i = 0; i < length; i++) {
      if(a[i*2] == a[(i*2)+1]) {
        a[i] = '1';
      } else {
        a[i] = '0';
      }
    }
    a[length] = 0;
  }
  printf("%s\n", a);
}
