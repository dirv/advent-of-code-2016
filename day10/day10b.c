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
bot outputs[100];

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
  } else {
    b->lowTo = &outputs[low];
  }
  if(highType =='b') {
    b->highTo = &bots[high];
  } else {
    b->highTo = &outputs[high];
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

int computeResult() {
  return outputs[0].high * outputs[1].high * outputs[2].high;
}

void run() {
  int result;
  while((result = computeResult()) == 0) {
    for(int i = 0; i < NUM_BOTS; ++i) {
      if(readyToConnect(&bots[i])) {
        moveBot(&bots[i]);
      }
    }
  }
  printf("%d\n", result);
}

int main(int argc, char** argv) {
  readInstructions();
  run();
  return 0;
}
