#include "my_malloc.h"
#include <unistd.h>

struct Node_t {
  size_t start_address;
  size_t end_address;
  size_t size;
  * struct Node_t next;
};
typedef struct Node_t Node;
//global variable to store the freed memory list
//Node * freedListHead;
Node * allocatedListHead;
size_t heapTop;
/* freedListHead.next = NULL; */
/* allocatedListHead.next = NULL; */


//First Fit malloc/free
void *ff_malloc(size_t size) {
  
  Node ** curr = &allocatedListHead;
  while (*curr->next != NULL) {
    if (*curr->next->next != NULL && (*curr->next->next->end_address - *curr->next) >= size) {
      Node * temp = *curr->next->next->end_address - 1;
      temp->start_address = temp - 1;
      temp->end_address = start_address - size;
      addToLinkedList(*curr, toBeMalloc);
    }
/*     if ((*curr)->next->size >= size + sizeof(*Node)) { */
/*       Node * toBeMalloc = (*curr)->next; */
/*       if (toBeMalloc->size == size) { */
/* 	Node * temp = toBeMalloc->next; */
/* 	addToLinkedList(allocatedListHead, toBeMalloc, 0); */
/* 	(*curr)->next = temp; */
/*       } else { */
/* 	Node * newFreeNode = ff_malloc(sizeof(*Node)); */
/* 	newFreeNode->size = mallocAddr->size - size; */
/* 	(*curr)->next->size -= size; */
/*       } */
/*       return (void *)toBeMalloc->start_address; */
/*     } */
    curr = &(*curr->next);
  }
  Node * temp = sbrk(sizeof(*temp));
  temp->size = sizeof(*temp);
  addToLinkedList(allocatedListHead, temp, size, 0);  
  temp = sbrk(size);
  temp->size = size;
  addToLinkedList(allocatedListHead, temp, size, 0);
  return NULL;
}
void ff_free(void *ptr) {
}
//Best Fit malloc/free
void *bf_malloc(size_t size) {
  return NULL;
}
void bf_free(void *ptr) {
}
