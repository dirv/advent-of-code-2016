#include "stdio.h"
#include "stdlib.h"

typedef enum { NORTH, SOUTH, EAST, WEST } direction;

const direction turns[] = { NORTH, WEST, SOUTH, EAST };
const int numTurns = 4;

direction turn(direction currentDirection, int increment) {
  for( int i = 0; i < numTurns; ++i ) {
    if( turns[i] == currentDirection ) {
      int nextPos = i + increment;
      if( nextPos == -1 ) {
        return turns[numTurns-1];
      } else if( nextPos == numTurns ) {
        return turns[0];
      } else {
        return turns[nextPos];
      }
    }
  }
  return NORTH;
}

int currentDirection = NORTH;
int currentVerticalDistance = 0;
int currentHorizontalDistance = 0;

void moveDistance(int distance) {
  switch(currentDirection) {
    case NORTH:
      currentVerticalDistance += distance;
      break;
    case SOUTH:
      currentVerticalDistance -= distance;
      break;
    case WEST:
      currentHorizontalDistance -= distance;
      break;
    case EAST:
      currentHorizontalDistance += distance;
      break;
  }
}

int main(int argc, char** argv) {
  FILE* fp = fopen("input.txt", "r");

  int north = 0;
  int south = 0;

  int c;
  int currentDistance = 0;
  while((c = fgetc(fp)) != EOF) {
    switch(c) {
      case 'L':
        currentDirection = turn(currentDirection, 1);
        break;
      case 'R':
        currentDirection = turn(currentDirection, -1);
        break;
      case ',':
        moveDistance(currentDistance);
        currentDistance = 0;
        break;
      case ' ':
        break;
      case '\n':
        break;
      default:
        currentDistance *= 10;
        currentDistance += c - '0';
    }
  }
  moveDistance(currentDistance);

  printf("%d\n", abs(currentHorizontalDistance) + abs(currentVerticalDistance));

  return 0;
}
