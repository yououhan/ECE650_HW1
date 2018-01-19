void addToLinkedList(Node * prev, Node * toBeAdded) {
  Node * temp = prev->next;
  prev->next = toBeAdded;
  toBeAdded->next = temp;
}

void deleteFromLinkedList(Node * prev, Node * toBeDeleted) {
  prev->next = toBeDeleted->next;
}

void initNode(Node * node, Node * prev, size_t size) {
  node->start_address = node - sizeof(*Node);
  node->end_address = node->start_address - size;
  addToLinkedList(prev, node);
}

//First Fit malloc/free
void *ff_malloc(size_t size) {
  Node * curr = allocatedListHead->next; 
  Node * prev = allocatedListHead;
  Node * temp = NULL;
  while (curr != NULL) {
    if ((curr->end_address - prev) >= size + sizeof(*Node)) {
       temp = curr->end_address - sizeof(*Node);
       break;
    }
    prev = curr;
    curr = curr->next;      
  }
  if (temp == NULL) {
    if ((headTop - prev) >= size + sizeof(*Node)) {
      temp = headTop;
    } else {
      temp = sbrk(size + sizeof(*Node) - headTop + prev);
      headTop = temp;
    }
  }
  initNode(temp, prev, size);
  return temp->start_address;       
}

void ff_free(void *ptr) {
  Node * curr = allocatedListHead->next; 
  Node * prev = allocatedListHead;
  while (curr != NULL) {
    if (curr->start_address == ptr) {
      deleteFromLinkedList(prev, curr);
      break;
    }
    prev = curr;
    curr = curr->next;
  }
}
