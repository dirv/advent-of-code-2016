#include "stdio.h"
#include "stdlib.h"

const int numDirections = 4;

int currentDirection = 0;
int movedDistances[] = {0, 0, 0, 0};

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

void moveDistance(int distance) {
  movedDistances[currentDirection] += distance;
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
        moveDistance(currentDistance);
        currentDistance = 0;
        break;
      default:
        if ( c >= '0' && c <= '9') {
          currentDistance *= 10;
          currentDistance += c - '0';
        }
    }
  }
  moveDistance(currentDistance);

  printf("%d\n", movedDistances[0]
      + movedDistances[1]
      - movedDistances[2]
      - movedDistances[3]);

  return 0;
}
