#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include <openssl/md5.h>


char *passcode = "dmypynyp";
//char *passcode = "ihgpwlah";

void toMd5(char *path, char *output) {
  char attempt[38] = { 0 };
  sprintf(attempt, "%s%s", passcode, path);
  unsigned char md5[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)attempt, strlen(attempt), md5);

  for(int i = 0; i < 16; i++) {
    sprintf(&output[i*2], "%02x", (unsigned int)md5[i]);
  }
}

typedef struct path {
  char path[30];
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

path* tryPaths(path *nextPath, path *lastPath) {
  printf("Trying %s\n", nextPath->path);
  fflush(NULL);
  if(isPathToVault(nextPath)) {
    return nextPath;
  }

  char md5[33];
  toMd5(nextPath->path, md5);
  path *newLastPath = lastPath;
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

  if(nextPath != newLastPath) {
    tryPaths(nextPath + 1, newLastPath);
  }
  return NULL;
}

int main(int argc, char **argv) {
  struct path paths[5000];
  struct path start = { "", 0, 0 };
  paths[0] = start;
  path *thisPath = tryPaths(&paths[0], &paths[1]);

  printf("%d\n", longestPath);
}
