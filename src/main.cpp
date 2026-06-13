#include <cstdio>
#include "chain.h"

int main() {
  Node* head = new Node{nullptr, 1, nullptr};

  insert(3, head, head);
  insert(5, head->next, head);

  Node* insert_pos = find(1, head);
  insert(4, insert_pos, head);

  Node* print_ptr = head;
  while (print_ptr != nullptr)
  {
    printf("%p address is %d\n", print_ptr, print_ptr->data);
    print_ptr = print_ptr->next;
  }
  
  return 0;
}