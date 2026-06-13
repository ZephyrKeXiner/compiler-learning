#pragma once

struct Node
{
  Node* prev;
  int data;
  Node* next;
};

void insert(int a, Node* pos, Node* root);
Node* find(int a, Node* root);
void del(int a);