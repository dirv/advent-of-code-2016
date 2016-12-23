#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

const int NUM_ELVES = 3014603;

typedef struct node {
  int elf;
  struct node *next;
  struct node *prev;
} node;

node* allocateAllNodes(int num) {
  node *head = (node*)malloc(sizeof(node));
  head->elf = 0;
  node *prev = head;
  node *next;
  for(int i = 1; i < num; ++i) {
    next = (node*)malloc(sizeof(node));
    next->elf = i;
    next->prev = prev;
    prev->next = next;
    prev = next;
  }
  next->next = head;
  head->prev = next;
  return head;
}

void deleteNode(node* n) {
  n->prev->next = n->next;
  n->next->prev = n->prev;
}

node* findNthNext(node *elf, int n) {
  node *current = elf;
  for(int i = 0; i < n; ++i) {
    current = current->next;
  }
  return current;
}

int main(int argc, char **argv) {
  int elvesLeft = NUM_ELVES;
  node* current = allocateAllNodes(NUM_ELVES);

  node *half = findNthNext(current, elvesLeft / 2);
  while(elvesLeft > 1) {
    deleteNode(half);
    current = current->next;
    half = half->next;
    if(elvesLeft % 2 != 0)
      half = half->next;
    elvesLeft--;
  }

  printf("%d\n", current->elf + 1);
  return 0;
}
