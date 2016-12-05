#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct letter {
  int count;
  int ch;
  struct letter *next;
} letter;

letter* removeOrCreateLetter(letter *head, int ch) {
  letter* next = head->next;
  if(next == NULL) {
    struct letter *l = (letter*)malloc(sizeof(letter));
    l->count = 0;
    l->ch = ch;
    l->next = NULL;
    return l;
  }
  if (next->ch == ch) {
    head->next = next->next;
    return next;
  }
  return removeOrCreateLetter(next, ch);
}

letter* findCorrectPlace(letter* head, letter* l) {
  letter* next = head->next;
  if (next == NULL) return head;
  if (l->count > next->count) {
    return head;
  }
  if(l->count == next->count) {
    if(l->ch < next->ch) {
      return head;
    }
  }
  return findCorrectPlace(next, l);
}

void insertAfter(letter* before, letter* l) {
  l->next = before->next;
  before->next = l;
}

void listToWord(letter *head, char* letters) {
  letter *current = head->next;
  for(int i = 0; i < 5; ++i) {
    letters[i] = current->ch;
    current = current->next;
  }
}

void topFiveLetters(char* s, char* letters) {
  int position = 0;
  int ch;
  letter head = {999, 0, NULL};
  while((ch = s[position++]) != '\0') {
    if(ch == '-') {
      continue;
    }
    struct letter *letter = removeOrCreateLetter(&head, ch);
    letter->count++;
    struct letter *place = findCorrectPlace(&head, letter);
    insertAfter(place, letter);
  }
  listToWord(&head, letters);
}

void decrypt(char *name, long sectorId) {
  long rotate = sectorId % 26;
  int current = 0;
  int ch;
  while((ch = name[current++]) != '\0') {
    if(ch == '-') {
      ch = ' ';
    } else {
      ch += rotate;
      if(ch > 'z') {
        ch -= 26;
      } else if (ch < 'a'){
        ch = '?';
      }
    }
    printf("%c", ch);
  }
  printf(" %d\n", sectorId);
}

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");

  int result;
  char name[200];
  char checksum[5];
  long sectorIdSum = 0;

  while((result = fscanf(fp, "%[a-z0-9-]\[%5s]\n", name, checksum)) != -1) {
    int length = strlen(name);
    char nameOnly[200] = { 0 };
    char topFive[5];
    strncpy(nameOnly, name, length - 4);
    topFiveLetters(nameOnly, topFive);

    if(strncmp(topFive, checksum, 5) == 0)
    {
      char *id = strrchr(name, '-') + 1;
      long sectorId = strtol(id, NULL, 10);
      sectorIdSum += sectorId;
      decrypt(nameOnly, sectorId);
    }
  }
  printf("%ld\n", sectorIdSum);

  fclose(fp);
  return 0;
}
