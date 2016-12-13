#include "stdio.h"
#include "stdbool.h"
#include "string.h"

const int NUM_CHIPS = 3;
const int NUM_FLOORS = 4;

typedef struct map {
  int elevator;
  bool microchips[NUM_FLOORS][NUM_CHIPS];
  bool generators[NUM_FLOORS][NUM_CHIPS];
} map;

map initialMap_ = {
  0,
  { { false, true, false, true, true, true, true },
    { true, false, true, false, false, false, false },
    { false },
    { false }},
  { { true, true, true, true, true, true, true },
    { false },
    { false },
    { false }}
};

map finalMap_ =  {
  3,
  { { false }, { false }, { false }, { true, true, true, true, true, true, true } },
  { { false }, { false }, { false }, { true, true, true, true, true, true, true } }
};

map initialMap = {
  3, { { false, true, true }, { false }, { false }, { true, false, false } },
  { { false, true, true }, { false }, { false }, { true, false, false } }
};

map finalMap =  {
  3,
  { { false }, { false }, { false }, { true, true, true} },
  { { false }, { false }, { false }, { true, true, true } }
};

void printMap(map *m) {
  for(int f = NUM_FLOORS - 1; f >= 0; --f) {
    printf("%d%c", f, m->elevator == f ? '*' : ' ');
    for(int i = 0; i < NUM_CHIPS; ++i) {
      printf("%d%d", m->microchips[f][i], m->generators[f][i]);
    }
    printf("\n");
  }
}

bool equal(map *a, map *b) {
  for(int f = 0; f < NUM_FLOORS; ++f)
    for(int i = 0; i < NUM_CHIPS; ++i) {
      if(a->generators[f][i] != b->generators[f][i]
          || a->microchips[f][i] != b->microchips[f][i]
          || a->elevator != b->elevator)
        return false;
    }

  return true;
}

bool allFloorsBelowEmpty(map* m) {
  int floor = m->elevator - 1;
  for(int f = floor; f >= 0; --f) {
    for (int i = 0; i < NUM_CHIPS; ++i) {
      if(m->microchips[f][i] || m->generators[f][i]) {
        return false;
      }
    }
  }
  return true;
}

bool generatorPresent(bool *generators) {
  for(int i = 0; i < NUM_CHIPS; ++i) {
    if(generators[i]) {
      return true;
    }
  }
  return false;
}

bool isFloorValid(bool *generators, bool *microchips) {
  bool anyGeneratorPresent = generatorPresent(generators);
  for(int i = 0; i < NUM_CHIPS; ++i) {
    if(microchips[i] && !generators[i] && anyGeneratorPresent) {
      return false;
    }
  }
  return true;
}

bool isMapValid(map *map) {
  for(int f = 0; f < NUM_FLOORS; ++f) {
    if(!isFloorValid(map->generators[f], map->microchips[f]))
      return false;
  }
  return true;
}

void saveIfValid(map **lastMap) {
  if (isMapValid(*lastMap)) {
    (*lastMap)++;
  }
}

void calculateNextMaps(map *currentMap, map **lastMap) {
  bool *generators = currentMap->generators[currentMap->elevator];
  bool *microchips = currentMap->microchips[currentMap->elevator];
  int elevator = currentMap->elevator;
  if (currentMap->elevator < NUM_FLOORS - 1) {
    for(int i = 0; i < NUM_CHIPS; ++i) {
      for(int j = 0; j < NUM_CHIPS; ++j) {
        if(generators[i] && microchips[j]) {
          memcpy(*lastMap, currentMap, sizeof(map));
          (*lastMap)->generators[elevator][i] = false;
          (*lastMap)->microchips[elevator][j] = false;
          (*lastMap)->elevator++;
          (*lastMap)->generators[elevator+1][i] = true;
          (*lastMap)->microchips[elevator+1][j] = true;
          saveIfValid(lastMap);
        }
      }
    }
    for(int i = 0; i < NUM_CHIPS; ++i) {
      for(int j = 0; j < NUM_CHIPS; ++j) {
        if(generators[i] && generators[j]) {
          memcpy(*lastMap, currentMap, sizeof(map));
          (*lastMap)->generators[elevator][i] = false;
          (*lastMap)->generators[elevator][j] = false;
          (*lastMap)->elevator++;
          (*lastMap)->generators[elevator+1][i] = true;
          (*lastMap)->generators[elevator+1][j] = true;
          saveIfValid(lastMap);
        }
      }
    }
    for(int i = 0; i < NUM_CHIPS; ++i) {
      for(int j = 0; j < NUM_CHIPS; ++j) {
        if(microchips[i] && microchips[j]) {
          memcpy(*lastMap, currentMap, sizeof(map));
          (*lastMap)->microchips[elevator][i] = false;
          (*lastMap)->microchips[elevator][j] = false;
          (*lastMap)->elevator++;
          (*lastMap)->microchips[elevator+1][i] = true;
          (*lastMap)->microchips[elevator+1][j] = true;
          saveIfValid(lastMap);
        }
      }
    }
  }
  if(currentMap->elevator > 0) {
    if (!allFloorsBelowEmpty(currentMap)) {
      for(int i = 0; i < NUM_CHIPS; ++i) {
        if(microchips[i]) {
          memcpy(*lastMap, currentMap, sizeof(map));
          (*lastMap)->microchips[elevator][i] = false;
          (*lastMap)->elevator--;
          (*lastMap)->microchips[elevator-1][i] = true;
          saveIfValid(lastMap);
        }
        if(generators[i]) {
          memcpy(*lastMap, currentMap, sizeof(map));
          (*lastMap)->generators[elevator][i] = false;
          (*lastMap)->elevator--;
          (*lastMap)->generators[elevator-1][i] = true;
          saveIfValid(lastMap);
        }
      }
    }
  }
}

bool inRoute(map *m, map *route, int numSteps) {
  for(int i = 0; i < numSteps; ++i) {
    if(equal(m, &route[i])) {
      return true;
    }
  }
  return false;
}

int findShortestRoute(map *allItems, map *nextItem, map *lastItem, int numSteps) {
  if(lastItem == nextItem){
    return -1;
  }
  printf("%d %ld %ld\n", numSteps, lastItem - allItems, nextItem - allItems);
  fflush(NULL);
  map *newLastItem = lastItem;
  for(map *m = nextItem; m < lastItem; ++m) {
    if(equal(m, &finalMap)) {
      return numSteps;
    }
    map possibleNextMaps[200];
    map *lastMap = possibleNextMaps;
    calculateNextMaps(m, &lastMap);

    for(map *n = possibleNextMaps; n < lastMap; ++n) {
      if(!inRoute(n, allItems, newLastItem - allItems)) {
        *newLastItem++ = *n;
      }
    }
  }

  return findShortestRoute(allItems, lastItem, newLastItem, numSteps + 1);
}

int main(int argc, char **argv) {
  map currentRoute[120000];
  currentRoute[0] = initialMap;
  printf("%d\n", findShortestRoute(currentRoute, currentRoute, currentRoute + 1, 0));
  return 0;
}
