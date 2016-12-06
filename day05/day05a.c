#include "stdio.h"
#include "string.h"
#include <openssl/md5.h>


int main(int argc, char** argv) {
  char *input = "ffykfhsq";

  char password[9] = { 0 };
  int currentCharacter = 0;

  char *prefix = "00000";

  int index = 0;
  while(1)
  {
    char md[33] = { 0 };
    char attempt[38] = { 0 };
    sprintf(attempt, "%s%d", input, index++);

    unsigned char md5[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)&attempt, strlen(attempt), (unsigned char*)&md5);

    for(int i = 0; i < 16; i++) {
      sprintf(&md[i*2], "%02x", (unsigned int)md5[i]);
    }

    if (strncmp(prefix, md, 5) == 0) {
      password[currentCharacter++] = md[5];
      if(currentCharacter == 8) {
        break;
      }
    }
  }

  printf("%s\n", password);
}
