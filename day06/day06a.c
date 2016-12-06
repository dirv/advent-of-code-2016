#include "stdio.h"

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");

  int letters[8][26];

  for(int i = 0; i < 8; ++i)
    for(int j = 0; j < 26; ++j)
      letters[i][j] = 0;

  char word[9] = { 0 };
  while(fscanf(fp, "%s\n", word) > 0) {
    for(int i = 0; i < 8; ++i) {
      int letter = word[i] - 'a';
      letters[i][letter]++;
    }
  }

  for(int i = 0; i < 8; ++i) {
    int max = 0;
    for(int j = 1; j < 26; ++j) {
      if (letters[i][j] > letters[i][max]) {
        max = j;
      }
    }
    printf("%c", max + 'a');
  }
  printf("\n");

  return 0;
}
