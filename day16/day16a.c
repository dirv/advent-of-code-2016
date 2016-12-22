#include "stdio.h"
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

int main(int argc, char **argv) {
  char a[500] = "11100010111110100";

  int length = strlen(a);
  int requiredLength = 272;

  while(length < requiredLength) {
    char b[500];
    strnrev(b, a, length);
    strswitch(b);
    strcat(a, "0");
    strcat(a, b);
    length *= 2;
    length++;
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
