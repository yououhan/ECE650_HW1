#include "my_malloc.h"
#include <unistd.h>

struct Node_t {
  size_t start_address;
  size_t end_address;
  //  size_t size;
  struct Node_t * next;
};
typedef struct Node_t Node;
//global variable to store the freed memory list
//Node * freedListHead;
Node * allocatedListHead;
void * heapTop;

void addToLinkedList(Node * prev, Node * toBeAdded) {
  Node * temp = prev->next;
  prev->next = toBeAdded;
  toBeAdded->next = temp;
}

void deleteFromLinkedList(Node * prev, Node * toBeDeleted) {
  prev->next = toBeDeleted->next;
}

void initNode(Node * node, Node * prev, size_t size) {
  node->start_address = (size_t)(node - 1);
  node->end_address = node->start_address - size;
  addToLinkedList(prev, node);
}

//First Fit malloc/free
void *ff_malloc(size_t size) {
  Node * curr = allocatedListHead->next; 
  Node * prev = allocatedListHead;
  Node * temp = NULL;
  while (curr != NULL) {
    if ((curr->end_address - (size_t)prev) >= size + sizeof(*curr)) {
      temp = (Node *)(curr->end_address - sizeof(*curr));
      break;
    }
    prev = curr;
    curr = curr->next;      
  }
  if (temp == NULL) {
    if (((size_t)heapTop - (size_t)prev) >= size + sizeof(*curr)) {
      temp = heapTop;
    } else {
      temp = sbrk(size + sizeof(*curr) - (size_t)heapTop + (size_t)prev);
      heapTop = temp;
    }
  }
  initNode(temp, prev, size);
  return (void *)(temp->start_address);
}

void ff_free(void *ptr) {
  Node * curr = allocatedListHead->next; 
  Node * prev = allocatedListHead;
  while (curr != NULL) {
    if (curr->start_address == (size_t)ptr) {
      deleteFromLinkedList(prev, curr);
      break;
    }
    prev = curr;
    curr = curr->next;
  }
}

//Best Fit malloc/free
void *bf_malloc(size_t size) {
  return NULL;
}
void bf_free(void *ptr) {
}
unsigned long get_data_segment_size() {
  Node * curr = allocatedListHead;
  unsigned long dataSize = 0;
  while (curr != NULL) {
    dataSize += curr->start_address - curr->end_address;
    curr = curr->next;
  }
  return dataSize;
}
unsigned long get_data_segment_free_space_size() {
  Node * curr = allocatedListHead;
  size_t counter = 0;
  while (curr != NULL) {
    counter++;
    curr = curr->next;
  }
  return (get_data_segment_size() - counter * sizeof(*curr));
}
