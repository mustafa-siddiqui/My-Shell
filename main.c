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
    printList(head);

    // insert '99' into list after the value '5'
    int* val1 = (int*) malloc(sizeof(int));
    *val1 = 5;
    int* val2 = (int*) malloc(sizeof(int));
    *val2 = 99;
    printf("Insert after\n");
    insertAfter(head, val1, val2);
    printList(head);
    printf("Completed");

    // insert '101' into list before the value '99'
    int* val3 = (int*) malloc(sizeof(int));
    assert(val3);
    *val3 = 1;
    int* val4 = (int*) malloc(sizeof(int)); 
    assert(val4);
    *val4 = 101;
    head = insertBefore(head, val3, val4);
    printf("Insert before\n");
    printList(head);

    // delete '99' from the list
    int* val5 = (int*) malloc(sizeof(int)); 
    *val5 = 99;
    deleteElement(head, val5);
    printf("Print after delete\n");
    printList(head);

    freeList(head);

    free(num);

    return 0;
}
