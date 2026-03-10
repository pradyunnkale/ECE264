// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h>
#include "hw10.h"

// DO NOT MODIFY this function --->>>
void printListNode(ListNode * head)
{
  ListNode * p = head;
  printf("printListNode: ");
  while (p != NULL) // the linked list must end with NULL
    {
      printf("%7d ", p -> value);
      p = p -> next;
    }
  printf("\n");
}
// <<<--- until here

// You MUST modify the following functions

#ifdef TEST_CREATELIST
// create a linked list storing values 0, 1, 2, ... valn - 1
// The first node (head) stores 0, the next node stores 1,
// ..., the last node stores valn - 1
// return the head of the linked listn
// the linked list must end with NULL

ListNode * createListHelper(int current, int valn);
ListNode * createListHelper(int current, int valn)
{
  if (current == valn) return NULL;
  ListNode * node = malloc(sizeof(ListNode));
  node->value = current;
  node->next = createListHelper(current + 1, valn);
  return node;
}

ListNode * createList(int valn)
{
  if (valn == 0) return NULL;
  ListNode * head = malloc(sizeof(ListNode));
  head->value = 0;
  head->next = createListHelper(1, valn);
  return head;
}

#endif

#ifdef TEST_ELIMINATE

void eliminateHelper(ListNode * head, ListNode * startNode, int valk);

// eliminate the nodes in the linked list
// starting from the head, move one node at a time and count to valk.
// eliminate that node, keep counting
//
// when reaching the end of the list, continue from the beginning of
// the list
//
// print the values of the nodes to be deleted
void eliminate(ListNode * head, int valk)
{
  if (head == NULL) return;
  if (head->next == NULL)
  {
    printf("%d\n", head->value);
    free(head);
    return;
  }

  ListNode * p = head;
  int i;
  for (i = 0; i < valk - 1; i++)
  {
    if (p->next == NULL) p = head;
    else p = p->next;
  }

#ifdef DEBUG
  // this #ifdef ... #endif should be inside the condition *BEFORE* a
  // node' value is printed and it is deleted
  ListNode * todelete = p;
  printListNode (todelete); 
#endif

  ListNode * nextNode = NULL; 
  if (p->next == NULL) nextNode = head;
  else nextNode = p->next;

  printf("%d\n", p->value);
  ListNode * newHead = deleteNode(head, p);
  eliminateHelper(newHead, nextNode, valk);
}

void eliminateHelper(ListNode * head, ListNode * startNode, int valk)
{
  if (head == NULL) return;
  if (head->next == NULL)
  {
    printf("%d\n", head->value);
    free(head);
    return;
  }

  ListNode * p = startNode;
  int i;
  for (i = 0; i < valk - 1; i++)
  {
    if (p->next == NULL) p = head;
    else p = p->next;
  }

#ifdef DEBUG
  // this #ifdef ... #endif should be inside the condition *BEFORE* a
  // node' value is printed and it is deleted
  ListNode * todelete = p;
  printListNode (todelete); 
#endif

  ListNode * nextNode = NULL; 
  if (p->next == NULL) nextNode = head;
  else nextNode = p->next;

  printf("%d\n", p->value);
  ListNode * newHead = deleteNode(head, p);
  eliminateHelper(newHead, nextNode, valk);
}
#endif

#ifdef TEST_DELETENODE
// head points to the first node in the linked list
// todelete points  to the node to be deleted
//
// delete the node and return the head of the linked list
// release the memory of the deleted node
//
// should check several conditions:
// 1. If head is NULL, the list is empty and this function returns NULL
// 2. If todelete is NULL, nothing can be deleted, return head
// 3. If todelete is not in the list, keep the list unchanged and
//    return head
// It is possible that todelete is the first node in the list (i.e.,
// the head). If this occurs, return the second node of the list.
ListNode * deleteNode(ListNode * head, ListNode * todelete)
{
  if (head == NULL) return NULL;
  if (todelete == NULL) return head;

  if (head == todelete)
  {
    ListNode * returnval = head->next;
    free(head);
    return returnval;
  }

  ListNode * prevNode = head;
  ListNode * nextNode = head;

  while (nextNode != NULL && nextNode != todelete)
  {
    prevNode = nextNode;
    nextNode = nextNode->next;
  }

  if (nextNode == NULL) return head;
  else
  {
    prevNode->next = nextNode->next;
    free(nextNode);
    return head;
  }

}
#endif


