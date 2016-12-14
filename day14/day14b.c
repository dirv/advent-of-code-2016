#include "stdio.h"
#include "string.h"
#include <openssl/md5.h>

const int LOOKBACK_COUNT = 1001;

char* findThreeRepeatedChars(char *candidate) {
  int startIndex = 0;
  char c;
  for(int i = 1; i < 33; ++i) {
    if(candidate[i] != candidate[i-1])
      startIndex = i;

    if(i - startIndex == 2)
      return &candidate[i];
  }
  return NULL;
}

void toMd5(char *salt, int index, char *output) {
  char attempt[MD5_DIGEST_LENGTH] = { 0 };
  sprintf(attempt, "%s%d", salt, index);
  unsigned char md5[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)attempt, strlen(attempt), md5);

  for(int i = 0; i < 16; i++) {
    sprintf(&output[i*2], "%02x", (unsigned int)md5[i]);
  }

  for(int i = 0; i < 2016; ++i) {
    MD5((unsigned char*)output, strlen(output), md5);

    for(int i = 0; i < 16; i++) {
      sprintf(&output[i*2], "%02x", (unsigned int)md5[i]);
    }
  }
}

int main(int argc, char **argv) {

  char *salt = "yjdafjpo";

  int index = 0;
  int numGeneratedKeys = 0;
  char candidates[1000][33];
  char md[33] = { 0 };
  while(index < 1000) {
    toMd5(salt, index, candidates[index]);
    index++;
  }

  while(numGeneratedKeys < 64) {
    char *r = findThreeRepeatedChars(candidates[(index-1000)%1000]);
    if (r != NULL) {
      char five[6] = {*r, *r, *r, *r, *r, 0};
      for(int i = index-999; i < index; ++i) {
        if(strstr(candidates[i%1000], five) != NULL) {
          numGeneratedKeys++;
          printf("%d\n", index-1000);
          break;
        }
      }
    }
    toMd5(salt, index, candidates[index%1000]);
    index++;
  }
}
