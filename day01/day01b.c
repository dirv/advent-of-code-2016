#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

const int numDirections = 4;

int currentDirection = 0;

typedef struct location {
  int x;
  int y;
} location;

location visited[10000];
int numVisited = 1;

void moveOne(location* loc) {
  switch(currentDirection) {
    case 0:
      loc->y++;
      break;
    case 1:
      loc->x++;
      break;
    case 2:
      loc->y--;
      break;
    case 3:
      loc->x--;
      break;
  }
}

void moveTo(int distance) {
  if(distance == 0) return;
  visited[numVisited] = visited[numVisited-1];
  moveOne(&visited[numVisited++]);
  moveTo(distance - 1);
}

bool equalLocation(location a, location b) {
  return a.x == b.x && a.y == b.y;
}

location* findFirstRepeat() {
  for(int i = 0; i < numVisited - 1; ++i) {
    for(int j = i+1; j < numVisited - 1; ++j) {
      if (equalLocation(visited[i], visited[j])) {
        return &visited[i];
      }
    }
  }
  return NULL;
}

void turnLeft() {
  if(currentDirection == 0) {
    currentDirection = numDirections;
  }
  currentDirection--;
}

void turnRight() {
  if(++currentDirection == numDirections) {
    currentDirection = 0;
  }
}

int locationDistance(location* loc) {
  return abs(loc->x) + abs(loc->y);
}

int main(int argc, char** argv) {
  FILE* fp = fopen("input.txt", "r");

  int c;
  int currentDistance = 0;
  while((c = fgetc(fp)) != EOF) {
    switch(c) {
      case 'L':
        turnLeft();
        break;
      case 'R':
        turnRight();
        break;
      case ',':
      case '\n':
        moveTo(currentDistance);
        currentDistance = 0;
        break;
      default:
        if ( c >= '0' && c <= '9') {
          currentDistance *= 10;
          currentDistance += c - '0';
        }
    }
  }
  location* repeat = findFirstRepeat();

  if(repeat != NULL) {
    printf("%d\n", locationDistance(repeat));
  }

  return 0;
}
