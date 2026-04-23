#include "huffman.h"
#include <stdlib.h>
#include <string.h>

TreeNode *buildTreeNode(int label, TreeNode *left, TreeNode *right)
{
  TreeNode *root = malloc(sizeof(TreeNode));

  if (root == NULL)
  {
    return NULL;
  }

  root->label = label;
  root->left = left;
  root->right = right;
  root->count = 0;

  if (left != NULL) 
  {
    root->count += left->count;
  }

  if (right != NULL)
  {
    root->count += right->count;
  }

  return root;
}

void freeHuffmanTree(TreeNode *ptr)
{
  if (ptr == NULL)
  {
    return;
  }
  freeHuffmanTree(ptr->left);
  freeHuffmanTree(ptr->right);
  free(ptr);
}


void huffmanPrintHelper(const TreeNode *node, FILE *fp, char *code, int depth);

void huffmanPrintHelper(const TreeNode *node, FILE *fp, char *code, int depth)
{
  if (node == NULL)
  {
    return;
  }

  if (isLeafNode(node))
  {
    code[depth] = '\0';

    fprintf(fp, "%c:%s\n", node->label, code);
  }

  code[depth] = '0';
  huffmanPrintHelper(node->left, fp, code, depth + 1);

  code[depth] = '1';
  huffmanPrintHelper(node->right, fp, code, depth + 1);
}

void huffmanPrint(const TreeNode *ptr, FILE *fp)
{
  if (ptr == NULL || fp == NULL)
  {
    return;
  }

  char code[ASCII_SIZE + 1];
  huffmanPrintHelper(ptr, fp, code, 0);
}

int isLeafNode(const TreeNode *node)
{
  return node != NULL && node->left == NULL && node->right == NULL;
}

long treeNodeCount(TreeNode *node)
{
  if (node == NULL)
  {
    return 0;
  }
  return node->count;
}

int treeNodeCompare(TreeNode *tp1, TreeNode *tp2)
{
  if (tp1 == NULL || tp2 == NULL)
  {
    return -2;
  }

  if (tp1->count > tp2->count)
  {
    return 1;
  }
  else if (tp1->count < tp2->count)
  {
    return -1;
  }

  if (isLeafNode(tp1) && !isLeafNode(tp2))
  {
    return -1;
  }

  if (!isLeafNode(tp1) && isLeafNode(tp2))
  {
    return 1;
  }

  if (isLeafNode(tp1) && isLeafNode(tp2))
  {
    if (tp1->label < tp2->label)
    {
      return -1;
    }

    if (tp1->label > tp2->label)
    {
      return 1;
    }
  }

  return 0;
}

TreeNode *buildHuffmanTree(ListNode *list)
{
  if (list == NULL)
  {
    return NULL;
  }

  while (list->next != NULL)
  {
    ListNode* a = removeListNode(&list);
    ListNode* b = removeListNode(&list);

    TreeNode *parent = buildTreeNode(-1, a->ptr, b->ptr);
    free(a);
    free(b);

    addListNode(&list, parent, treeNodeCompare);
  }

  TreeNode *root = list->ptr;
  free(list);
  return root;
}

ListNode *addListNode(ListNode **list, TreeNode *new_object, 
                  int (*cmpFunction)(TreeNode *, TreeNode *))
{
  if (list == NULL || new_object == NULL || cmpFunction == NULL)
  {
    return NULL;
  }

  ListNode * add = malloc(sizeof(ListNode));
  if (add == NULL)
  {
    return NULL;
  }
  add->ptr = new_object;
  add->next = NULL;

  if (*list == NULL || cmpFunction(new_object, (*list)->ptr) < 0)
  {
    add->next = *list;
    *list = add;
    return add;
  }

  ListNode *curr = *list;
  while(curr->next != NULL && cmpFunction(new_object, curr->next->ptr) >= 0)
  {
    curr = curr->next;
  }

  add->next = curr->next;
  curr->next = add;

  return add;
}

ListNode *removeListNode(ListNode** list)
{
  if (list == NULL || *list == NULL)
  {
    return NULL;
  }

  ListNode *removed = *list; // Remove the first node in the list
  *list = removed->next;
  removed->next = NULL;
  return removed;
}

void freeList(ListNode *list)
{
  while (list != NULL)
  {
    ListNode *next = list->next;
    free(list);
    list = next;
  }
}

void printList(const ListNode *list, FILE * fp)
{
  if (list == NULL || fp == NULL)
  {
    return;
  }

  while (list != NULL)
  {
    if (list->ptr != NULL)
    {
      fprintf(fp, "%c:%ld\n", list->ptr->label, list->ptr->count);
    }
    list = list->next;
  }
}
