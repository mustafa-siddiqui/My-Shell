/**
 *  @file   main.c
 *  @brief  The driver code for the shell program.
 *  @author Mustafa Siddiqui
 *  @date   06/26/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// -- //
#include "linked_list.h"
#include "msh.h"

int main(void) {

    char** tokens = parseLine(readLine());
    int i = 0;
    while (tokens[i] != NULL) {
        printf("%s\n", tokens[i]);
        i++;
    }

    int* num = (int*) malloc(sizeof(int));
    *num = 1;
    Node* head = createNode(INTEGER, num);
    // populate list and print
    for (int i = 1; i < 10; i++) {
        int* val = (int*) malloc(sizeof(int));
        *val = i + 1;
        head = append(head, val);
    }
    printf("Initial print list\n");
    printList(head);

    // insert '99' into list after the value '5'
    int* val1 = (int*) malloc(sizeof(int));
    *val1 = 5;
    int* val2 = (int*) malloc(sizeof(int));
    *val2 = 99;
    printf("Insert %d after %d\n", *val2, *val1);
    insertAfter(head, val1, val2);
    printList(head);

    // insert '101' into list before the value '1'
    int* val3 = (int*) malloc(sizeof(int));
    assert(val3);
    *val3 = 1;
    int* val4 = (int*) malloc(sizeof(int)); 
    assert(val4);
    *val4 = 101;
    head = insertBefore(head, val3, val4);
    printf("Insert %d before %d\n", *val4, *val3);
    printList(head);

    // delete '99' from the list
    int* val5 = (int*) malloc(sizeof(int)); 
    *val5 = 99;
    deleteElement(head, val5);
    printf("Print after delete\n");
    printList(head);

    // search '5' in the list
    int* val6 = _ALLOC_MEM(int);
    *val6 = 87;
    i = 0;
    if ((i = search(head, val6)) != -1)
        printf("87 found at %d\n", i);
    else
        printf("87 not in list\n");

    freeList(head);

    return 0;
}
