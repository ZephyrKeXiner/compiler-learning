#include "chain.h"
#include <cstdio>

void insert(int a, Node* pos, Node* root) {
  Node* node_address = root;

  if (pos == nullptr)
  {
    return;
  }
  
  Node* new_node = new Node{pos, a, pos->next};
  pos->next = new_node;
}

Node* find(int a, Node* root) {
  Node* node = root;
  
  while (node->data != a)
  {
    node = node->next;
  }

  return node;
}

Node* del()

