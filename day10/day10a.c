#include "stdio.h"
#include "stdbool.h"

typedef struct bot {
  int high;
  int low;
  struct bot* highTo;
  struct bot* lowTo;
} bot;

const int NUM_BOTS = 300;
bot bots[NUM_BOTS];

void addValueToBot(int value, bot *b) {
  if(b->high == 0) {
    b->high = value;
  } else if(b->high > value) {
    b->low = value;
  } else {
    b->low = b->high;
    b->high = value;
  }
}

void addConnectionsToBot(bot *b, char lowType, int low, char highType, int high) {
  if(lowType == 'b') {
    b->lowTo = &bots[low];
  }
  if(highType =='b') {
    b->highTo = &bots[high];
  }
}

void readValue(FILE *fp) {
  int bot;
  int value;
  fscanf(fp, "%d goes to bot %d", &value, &bot);
  addValueToBot(value, &bots[bot]);
}

void readConnections(FILE *fp) {
  int bot, low, high;
  char lowType[10], highType[10];
  fscanf(fp, "%d gives low to %s %d and high to %s %d\n",
      &bot, lowType, &low, highType, &high);
  addConnectionsToBot(&bots[bot], lowType[0], low, highType[0], high);
}

void readInstructions() {
  FILE *fp = fopen("input.txt", "r");
  int result;
  char command[7];
  while((result = fscanf(fp, "%s", command)) != -1) {
    if(command[0] == 'v')
      readValue(fp);
    else
      readConnections(fp);
  }
}

bool thisBotIsResponsible(bot *b) {
  return (b->low == 17 && b->high == 61);
}

bool readyToConnect(bot *b) {
  return b->low != 0 && b->high != 0;
}

void moveBot(bot *b) {
  if(b->highTo != NULL) {
    addValueToBot(b->high, b->highTo);
  }
  if(b->lowTo != NULL) {
    addValueToBot(b->low, b->lowTo);
  }
  b->high = 0;
  b->low = 0;
}

void run() {
  int foundBot = 0;
  while(foundBot == 0) {
    for(int i = 0; i < NUM_BOTS; ++i) {
      if(thisBotIsResponsible(&bots[i])) {
        foundBot = i;
        break;
      }
      if(readyToConnect(&bots[i])) {
        moveBot(&bots[i]);
      }
    }
  }
  printf("%d\n", foundBot);
}

int main(int argc, char** argv) {
  readInstructions();
  run();
  return 0;
}
