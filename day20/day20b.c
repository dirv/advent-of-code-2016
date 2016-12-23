#include "stdio.h"
#include "stdbool.h"

typedef struct range {
  long low;
  long high;
  struct range *next;
} range;

void insert(range *head, range *r) {
  range *current = head;
  while(current != NULL) {
    if(current->next != NULL && current->next->low == r->low) {
      printf("oh der");
    }
    if(current->next == NULL || current->next->low > r->low) {
      r->next = current->next;
      current->next = r;
      break;
    }
    current = current->next;
  }
}

range ranges[2000];

int main(int argc, char** argv) {
  FILE *fp = fopen("input.txt", "r");
  int num = 0;
  struct range head = { -1, -1 };
  while(fscanf(fp, "%ld-%ld",&ranges[num].low, &ranges[num].high) > 0) {
    insert(&head, &ranges[num]);
    num++;
  }

  long curMin = 0;
  long allowed = 0;

  range* current = head.next;
  while(current != NULL) {
    if(current->low > curMin)
      allowed += current->low - curMin;
    if(current->high + 1 > curMin)
      curMin = current->high + 1;
    current = current->next;
  }
  printf("%ld\n", allowed);
}
