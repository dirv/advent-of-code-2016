#include "stdio.h"
#include "stdbool.h"

const int seed = 1350;

typedef struct location {
  int x, y;
} location;

const int MAZE_SIZE = 50;

bool isWall(int x, int y) {
  if(x < 0 || y < 0) return true;
  unsigned int sum = x*x + 3*x + 2*x*y + y + y*y + seed;
  int count = __builtin_popcount(sum);
  if(count % 2 == 0) return false;
  return true;
}

bool alreadyVisited(location *l, location *start, location *stop) {
  for(location *m = start; m < stop; ++m)
    if (m->x == l->x && m->y == l->y)
      return true;
  return false;
}

bool canAdd(location *l, location *start, location *stop) {
  return !isWall(l->x, l->y) && !alreadyVisited(l, start, stop);
}

void save(location *l, location **nextMap) {
  (*nextMap)->x = l->x;
  (*nextMap)->y = l->y;
  (*nextMap)++;
}

void addNextSpots(location *l, location *start, location **next) {
  location up = { l->x, l->y - 1};
  location down = { l->x, l->y + 1};
  location left = { l->x - 1, l->y };
  location right = {l->x + 1, l->y };
  if (canAdd(&up, start, *next)) save(&up, next);
  if (canAdd(&down, start, *next)) save(&down, next);
  if (canAdd(&left, start, *next)) save(&left, next);
  if (canAdd(&right, start, *next)) save(&right, next);
}

int findAllLocations(location *allLocations, location *next, location *last, int numSteps) {
  if(numSteps == 50)
    return last - allLocations;

  location *newLast = last;
  for(location *l = next; l < last; ++l) {
    addNextSpots(l, allLocations, &newLast);
  }
  if(last == newLast) {
    return -1;
  }
  return findAllLocations(allLocations, last, newLast, numSteps + 1);
}

int main(int argc, char** argv) {
  location allLocations[100000];
  struct location first = { 1, 1 };
  allLocations[0] = first;
  printf("%d\n", findAllLocations(allLocations, allLocations, allLocations + 1, 0));
}
