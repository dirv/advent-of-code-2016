#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct instruction {
  char type;
  int *operands[2];
} instruction;

int registers[4] = { 0 };

bool isRegister(char *val) {
  return (val[0] >= 'a' && val[0] <= 'd');
}

int *getRegister(char val) {
  return &registers[val-'a'];
}

int *toVal(char *s) {
  int *p = (int*)malloc(sizeof(int));
  *p = strtol(s, NULL, 10);
  return p;
}

void readCopy(FILE *fp, instruction *in) {
  char val[20];
  char reg;
  fscanf(fp, "%s %c", val, &reg);
  if (isRegister(val)) {
    in->operands[0] = getRegister(val[0]);
  } else {
    in->operands[0] = toVal(val);
  }
  in->operands[1] = getRegister(reg);
}

void readSingle(FILE *fp, instruction *in) {
  char val;
  fscanf(fp, " %c", &val);
  in->operands[0] = getRegister(val);
}

void readJnz(FILE *fp, instruction *in) {
  char distance[20];
  char val[20];
  fscanf(fp, "%s %s", val, distance);
  if(isRegister(val)) {
    in->operands[0] = getRegister(val[0]);
  } else {
    in->operands[0] = toVal(val);
  }
  in->operands[1] = toVal(distance);
}

void run(instruction *instructions, instruction *last) {
  instruction *current = instructions;
  while(current < last) {
    switch(current->type) {
      case 'c':
        *current->operands[1] = *current->operands[0];
        current++;
        break;
      case 'i':
        (*current->operands[0])++;
        current++;
        break;
      case 'd':
        (*current->operands[0])--;
        current++;
        break;
      default:
        if(*current->operands[0] != 0)
          current += *current->operands[1];
        else
          current++;
        break;
    }
  }
}

int main(int argc, char **argv) {
  FILE *fp = fopen("input.txt", "r");

  instruction instructions[300];
  instruction *current = instructions;
  char instruction[4];
  while(fscanf(fp, "%3s", instruction) > 0) {
    struct instruction newInstruction = { instruction[0], { 0 } };
    *current = newInstruction;
    switch(instruction[0]) {
      case 'c':
        readCopy(fp, current);
        break;
      case 'i':
        readSingle(fp, current);
        break;
      case 'd':
        readSingle(fp, current);
        break;
      case 'j':
        readJnz(fp, current);
        break;
    }
    current++;
  }

  run(instructions, current);

  printf("%d\n", *getRegister('a'));
  return 0;
}
