#include "stdio.h"
#include "string.h"

int screen[50][6];

void rect(FILE *fp) {
  int rows, columns;
  fscanf(fp, "%dx%d\n", &rows, &columns);
  for(int i = 0; i < rows; ++i)
    for(int j = 0; j < columns; ++j)
      screen[i][j] = 1;
}

void rotateRow(int row, int amount) {
  int newScreen[50];
  for(int i = 0; i < 50; ++i) {
    int oldRow = i - amount;
    if(oldRow < 0) oldRow += 50;
    newScreen[i] = screen[oldRow][row];
  }
  for(int i = 0; i < 50; ++i) {
    screen[i][row] = newScreen[i];
  }
}

void rotateColumn(int column, int amount) {
  int newScreen[6];
  for(int i = 0; i < 6; ++i) {
    int oldColumn = i - amount;
    if(oldColumn < 0) oldColumn += 6;
    newScreen[i] = screen[column][oldColumn];
  }
  for(int i = 0; i < 6; ++i) {
    screen[column][i] = newScreen[i];
  }
}

void rotate(FILE *fp) {
  char type[50];
  fscanf(fp, "%s", &type);
  if(type[0] == 'r') {
    int row, amount;
    fscanf(fp, " y=%d by %d\n", &row, &amount);
    rotateRow(row, amount);
  } else {
    int column, amount;
    fscanf(fp, " x=%d by %d\n", &column, &amount);
    rotateColumn(column, amount);
  }
}

int addAllScreen() {
  int counter = 0;
  for ( int i = 0; i < 50; ++ i)
    for ( int j =0; j < 6; ++j)
      counter += screen[i][j];
  return counter;
}

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");

	int result;
  char word[50];
	while((result = fscanf(fp, "%s", &word)) > 0) {
    if (strncmp("rect", word, 4) == 0)
      rect(fp);
    if (strncmp("rotate", word, 4) == 0)
      rotate(fp);

  }

  printf("%d\n", addAllScreen());

  for(int i = 0; i < 6; ++i) {
    for(int j = 0; j < 50; ++j)
      printf("%c", screen[j][i] == 1 ? '#' : ' ');
    printf("\n");
  }
  return 0;
}
