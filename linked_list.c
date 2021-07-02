/** 
 *  @file   linked_list.c
 *  @brief  Function definitions for implementing linked lists.
 *  @author Mustafa Siddiqui
 *  @date   06/26/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// -- //
#include "linked_list.h"

/* Compare data pointed to by two void pointers as per the specified data type */
int compare(void* ptr1, void* ptr2, DATA_TYPES dataType) {
    int notEqual = 0;
    switch (dataType) {
        case INTEGER:
            notEqual = _COMPARE(ptr1, ptr2, int);
            break;
        case DOUBLE:
            notEqual = _COMPARE(ptr1, ptr2, double);
            break;
        case CHAR:
            notEqual = _COMPARE(ptr1, ptr2, char);
            break;
        case STRING:
            notEqual = _STR_COMPARE(ptr1, ptr2);
            break;
        default:
            printf("Invalid data type at %d in %s().\n", __LINE__, __FUNCTION__);
            exit(EXIT_FAILURE);
        }

    return notEqual;
}

/* Print data in a node in the linked list in preset format */
void printListElem(void* ptr, DATA_TYPES dataType) {
    switch (dataType) {
        case INTEGER:
            printf("%d -> ", _ACCESS_VALUE(ptr, int));
            break;
        case DOUBLE:
            printf("%.2f -> ", _ACCESS_VALUE(ptr, double));
            break;
        case CHAR:
            printf("%c -> ", _ACCESS_VALUE(ptr, char));
            break;
        case STRING:
            printf("%s -> ", _ACCESS_VALUE(ptr, char*));
            break;
        default:
            printf("Invalid data type at %d in %s().\n", __LINE__, __FUNCTION__);
            exit(EXIT_FAILURE);
    }
}

/* Create new node as per the specified data type */
Node* createNode(DATA_TYPES dataType, void* val) {
    Node* newNode = _ALLOC_MEM(Node);
    newNode->dataType = dataType;
    newNode->next = NULL;
    switch(dataType) {
        case INTEGER:
            newNode->value = _ALLOC_MEM(int);
            newNode->value = _ASSIGN(val, int);
            break;
        case DOUBLE:
            newNode->value = _ALLOC_MEM(double);
            newNode->value = _ASSIGN(val, double);
            break;
        case CHAR:
            newNode->value = _ALLOC_MEM(char);
            newNode->value = _ASSIGN(val, char);
            break;
        case STRING:
            newNode->value = _ALLOC_MEM(char*);
            newNode->value = _ASSIGN(val, char*);
            break;
        default:
            fprintf(stderr, "Invalid data type for linked list.\n");
            exit(EXIT_FAILURE);
    }

    return newNode;
}

/* Append at end of list */
Node* append(Node* head, void* value) {
    // exit if data of different types
    _TYPE_CHECK(head->value, value);

    DATA_TYPES dataType = head->dataType;

    // create new node
    Node* newNode = createNode(dataType, value);

    // if list empty, new node will become head
    if (head == NULL) {
        return newNode;
    }

    // iterate to the end of the list
    Node* currentNode = head;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }

    // append new node
    currentNode->next = newNode;

    return head;
}

/* Insert value into list after some value. */
void insertAfter(Node* head, void* valueBeforeInsert, void* insertValue) {
    // exit if data of different types
    _TYPE_CHECK(head->value, valueBeforeInsert);

    Node* currentNode = head;

    // iterate over list until value reached
    int notEqual = 1;
    while (notEqual) {
        notEqual = compare(currentNode->value, valueBeforeInsert, currentNode->dataType);

        // break so to not change the current node
        if (!notEqual)
            break;

        currentNode = currentNode->next;

        // return if value not in list
        if (currentNode == NULL) {
            printf("valueBeforeInsert not in list in %s()\n", __FUNCTION__);
            return;
        }
    }

    // create node to be inserted
    Node* insertNode = createNode(head->dataType, insertValue);
    insertNode->next = currentNode->next;

    // make current node point to node to be inserted (which points to the next node)
    currentNode->next = insertNode;
}

/* Insert value into list before some value. */
Node* insertBefore(Node* head, void* valueAfterInsert, void* insertValue) {
    // exit if data of different types
    _TYPE_CHECK(head->value, valueAfterInsert);

    Node* currentNode = head;
    Node* previousNode = NULL;
    
    // iterate over loop until value reached
    int notEqual = 1;
    while (notEqual) {
        notEqual = compare(currentNode->value, valueAfterInsert, currentNode->dataType);
        
        // break so to not change the current node
        if (!notEqual)
            break;

        previousNode = currentNode;
        currentNode = currentNode->next;

        // return if value not in list
        if (currentNode == NULL) {
            printf("valueAfterInsert not in list in %s()\n", __FUNCTION__);
            return head;
        }
    }

    // create node to be inserted
    Node* insertNode = createNode(head->dataType, insertValue);
    insertNode->next = currentNode;

    // if value is to be inserted before head
    // currentNode will be the same as head in this case
    int updateHead = compare(head->value, insertValue, head->dataType);
    if (updateHead) {
        head = insertNode;
    }
    else {
        // make node before search value node point to node to be inserted (which points to the next node)
        // previousNode will not be NULL since have iterated over list
        previousNode->next = insertNode;
    }

    return head;
}

/* Delete value from list. */
void deleteElement(Node* head, void* valueToDelete) {
    // exit if data of different types
    _TYPE_CHECK(head->value, valueToDelete);

    Node* currentNode = head;
    Node* previousNode = NULL;

    // iterate over list until value to be deleted is reached
    int notEqual = 1;
    while (notEqual) {
        notEqual = compare(currentNode->value, valueToDelete, head->dataType);

        // break so to not change the current node
        if (!notEqual)
            break;
        
        previousNode = currentNode;
        currentNode = currentNode->next;

        // return if value not in list
        if (currentNode == NULL) {
            printf("valueToDelete not in list in function %s()\n", __FUNCTION__);
            return;
        }
    }

    // connect previous and after nodes
    previousNode->next = currentNode->next;

    // free node with value to be deleted
    free(currentNode);
}

/* Search value in list. */
int search(Node* head, void* valueToSearch) {
    Node* currentNode = head;

    // iterate over list until value is found or till end of list while
    // keeping track of how many iterations made
    int index = 0;
    int notEqual = 1;
    while (notEqual) {
        notEqual = compare(currentNode->value, valueToSearch, currentNode->dataType);

        // break so to not change the current node
        if (!notEqual)
            break;
        
        currentNode = currentNode->next;
        index++;

        if (currentNode == NULL) {
            // value not found, return -1
            return -1;
        }
    }

    return index;
}

/* Print list. */
void printList(Node* head) {
    Node* currentNode = head;

    // iterate over list and print values
    while (currentNode != NULL) {
        printListElem(currentNode->value, head->dataType);

        currentNode = currentNode->next;
        printf("Iterating over\t");     // debug statement
    }
    printf("printing new line\n");      // debug statement
    putchar('\n');
}

/* Print list in reverse. */
void printListReverse(Node* head) {
    // base case
    if (head == NULL) {
        return;
    }
    
    // recursive call to next node
    printListReverse(head->next);

    // print data
    printListElem(head->value, head->dataType);
}

/* Free up memory allocated for list. */
void freeList(Node* head) {
    Node* currentNode = head;
    Node* previousNode = NULL;

    // iterate over the list and free nodes as we go
    while (currentNode != NULL) {
        previousNode = currentNode;
        currentNode = currentNode->next;

        printf("Freeing %d\n", *((int*)previousNode->value));   // debug statement
        free(previousNode->value);
        free(previousNode);
    }
}
