#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#include <openssl/md5.h>


char *passcode = "dmypynyp";
//char *passcode = "ihgpwlah";
int longestPath = 0;

void toMd5(char *path, char *output) {
  char attempt[38000] = { 0 };
  sprintf(attempt, "%s%s", passcode, path);
  unsigned char md5[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)attempt, strlen(attempt), md5);

  for(int i = 0; i < 16; i++) {
    sprintf(&output[i*2], "%02x", (unsigned int)md5[i]);
  }
}

typedef struct path {
  char path[1000];
  int x;
  int y;
} path;


bool isPathToVault(path *path) {
  return path->x == 3 && path->y == 3;
}

bool isValid(path *path) {
  return path->x >= 0 && path->x <= 3
    && path->y >= 0 && path->y <= 3;
}

bool isOpen(char letter) {
  return letter > 'a';
}

const int SIZE = 2500000;

void tryPaths(path *nextPath, path *lastPath) {
  path *newLastPath = lastPath;
  char md5[33];
  int i;
  while(nextPath != newLastPath) {
    if(isPathToVault(nextPath)) {
      longestPath = strlen(nextPath->path);
    } else {
      toMd5(nextPath->path, md5);
      if(isOpen(md5[0])) {
        memcpy(newLastPath, nextPath, sizeof(path));
        strcat(newLastPath->path, "U");
        newLastPath->y--;
        if(isValid(newLastPath)) newLastPath++;
      }
      if(isOpen(md5[1])) {
        memcpy(newLastPath, nextPath, sizeof(path));
        strcat(newLastPath->path, "D");
        newLastPath->y++;
        if(isValid(newLastPath)) newLastPath++;
      }
      if(isOpen(md5[2])) {
        memcpy(newLastPath, nextPath, sizeof(path));
        strcat(newLastPath->path, "L");
        newLastPath->x--;
        if(isValid(newLastPath)) newLastPath++;
      }
      if(isOpen(md5[3])) {
        memcpy(newLastPath, nextPath, sizeof(path));
        strcat(newLastPath->path, "R");
        newLastPath->x++;
        if(isValid(newLastPath)) newLastPath++;
      }
    }
    nextPath++;
  }
}

int main(int argc, char **argv) {
  path *paths = (path*)malloc(sizeof(path)*SIZE);
  struct path start = { "", 0, 0 };
  paths[0] = start;
  tryPaths(&paths[0], &paths[1]);

  printf("%d\n", longestPath);
}
