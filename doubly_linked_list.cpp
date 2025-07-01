//=================================================================
// Implementation for DLL module.
//
// Copyright 2021 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include "doubly_linked_list.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>

LLNode *create_llnode(void *data) {
  /**
   * TODO: Implement the method as described in the header file 
   *    to create a DLL node 
   */
  LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
  newNode->prev = NULL;
  newNode->next = NULL;
  newNode->data = data;
  return newNode;
}

DLinkedList *create_dlinkedlist(void) {
  DLinkedList *newList = (DLinkedList *)malloc(sizeof(DLinkedList));
  newList->head = NULL;
  newList->tail = NULL;
  newList->size = 0;
  return newList;
}

void insertHead(DLinkedList *dLinkedList, void *data) {
  /**
   * TODO: Implement the method as described in the header file 
   *    to insert a node at the head of the DLL
   */

   // 1. Create the node

   // 2. Insert the newly created node into the DLL. 
   //   HINT: When a DLL has a single node, that head and the
   //    tail points to the same node.

   // 3. Update the size of the DLL
   LLNode *newNode = create_llnode(data);
   if (dLinkedList->size == 0) {
       dLinkedList->head = newNode;
       dLinkedList->tail = newNode;
       dLinkedList->size++;
       return;
   }
   newNode->next = dLinkedList->head;
   dLinkedList->head->prev = newNode;
   dLinkedList->head = newNode;
   dLinkedList->size++;
}

void deleteNode(DLinkedList *dLinkedList, LLNode *Node) {
  /**
   * TODO: Implement the method as described in the header file 
   *    to delete a node from the DLL
   */

    // HINT: Remember to free memory that would have been allocated
    int index = 0;
    if (dLinkedList == NULL) {
        return;
    }
    LLNode *tempNode = dLinkedList->head;
    while (index < dLinkedList->size) {
        if (tempNode == Node) {
            if (index == 0) {
                dLinkedList->head = dLinkedList->head->next;
                if (dLinkedList->head->next == NULL) {
                    dLinkedList->tail = NULL;
                } else {
                    dLinkedList->head->prev = NULL;
                }
                free(tempNode);
                dLinkedList->size--;
                return;
            } else if (index == dLinkedList->size - 1) {
                dLinkedList->tail = dLinkedList->tail->prev;
                if (dLinkedList->tail == NULL) {
                    dLinkedList->head = NULL;
                } else {
                    dLinkedList->tail-> next = NULL; 
                }
                free(tempNode);
                dLinkedList->size--;
                return;
            } else {
                tempNode->prev->next = tempNode->next;
                tempNode->next->prev = tempNode->prev;
                free(tempNode);
                dLinkedList->size--;
                return;
            }
        } else {
            index++;
            tempNode = tempNode->next;
        }
    }
    return;


}

void destroyList(DLinkedList *dLinkedList) {
  LLNode *Node = dLinkedList->head;
  LLNode *Next;
  while (Node) {
    free(Node->data);
    Next = Node->next;
    free(Node);
    Node = Next;
  }
  free(dLinkedList);
}

int getSize(DLinkedList *dLinkedList) { return dLinkedList->size; }

// Check for common errors and ASSERT_P to raise the error code.
void testDLL(void) {
  int n = 4;
  LLItem *m[n];
  DLinkedList *myList = create_dlinkedlist();
  while (n--)
    m[n] = (LLItem *)malloc(sizeof(LLItem));


  for (n = 0; n < 3; n++) {
    insertHead(myList, m[n]);
    if ((myList->head->data != m[n]) || (getSize(myList) != n + 1))
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(myList->head->data == m[n], ERROR_DLL_INSERT_HEAD);
    ASSERT_P(getSize(myList) == n + 1, ERROR_DLL_INSERT_HEAD);
  }


  // [2 1 0]
  LLNode *current = myList->head;
  for (n = 2; n >= 0; n--) {
    if (current->data != m[n])
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(current->data == m[n], ERROR_DLL_INSERT_HEAD);
    current = current->next;
  }
  pc.printf("OK DLL 3 x insertHead: [2 1 0]\n");
  uLCD.printf("OK DLL 3 inserts:\n    [2 1 0]\n");
  deleteNode(myList, myList->head->next); // delete middle node
  if (getSize(myList) != 2)
    uLCD.printf("Complete and debug DLL to get rid of this error\n");
  ASSERT_P(getSize(myList) == 2, ERROR_DLL_DELETE);
  // [2 0]
  current = myList->head;
  for (n = 2; n >= 0; n = n - 2) {
    if (current->data != m[n])
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(current->data == m[n], ERROR_DLL_DELETE);
    current = current->next;
  }
  pc.printf("OK DLL deleteNode middle: [2 0]\n");
  uLCD.printf("OK DLL del mid:\n    [2 0]\n");
  insertHead(myList, m[3]); // 3 2 0
  if (getSize(myList) != 3)
    uLCD.printf("Complete and debug DLL to get rid of this error\n");
  ASSERT_P(getSize(myList) == 3, ERROR_DLL_INSERT_HEAD);
  pc.printf("OK DLL insertHead: [3 2 0]\n");
  uLCD.printf("OK DLL 1 ins:\n    [3 2 0]\n");
  deleteNode(myList, myList->head); // delete head
  if (getSize(myList) != 2)
    uLCD.printf("Complete and debug DLL to get rid of this error\n");
  ASSERT_P(getSize(myList) == 2, ERROR_DLL_DELETE);
  current = myList->head;

  
  // [2 0]
  for (n = 2; n >= 0; n = n - 2) {
    if (current->data != m[n])
      uLCD.printf("Complete and debug DLL to get rid of this error\n");
    ASSERT_P(current->data == m[n], ERROR_DLL_DELETE);
    current = current->next;
  }
  pc.printf("OK DLL deleteNode head: [2 0]\n");
  uLCD.printf("OK DLL del head:\n    [2 0]\n");
  destroyList(myList);
}
