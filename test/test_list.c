/**
 *  @file   main.c
 *  @brief  Test file to test the linked list for the
 *          supported data types.
 *  @author Mustafa Siddiqui
 *  @date   07/01/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// -- //
#include "../src/linked_list.h"

/*
    Helpful macro to declare and set value for variable given
    the datatype. ** uses pointers, not basic variables **
    => requires assert.h to check memory allocation <=
*/
#define SET(val, var, type) type* var = _ALLOC_MEM(type);   \
                            assert(var);                    \
                            *var = val

int main(void) {
//#define INTEGER_LIST
#ifdef INTEGER_LIST
    SET(1, num, int);
    Node* head = createNode(INTEGER, num);
    // populate list and print
    for (int i = 1; i < 10; i++) {
        SET(i + 1, val, int);
        head = append(head, val);
    }
    printf("Initial print list\n");
    printList(head);

    // insert '99' into list after the value '5'
    SET(5, val1, int);
    SET(99, val2, int);
    printf("Insert %d after %d\n", *val2, *val1);
    insertAfter(head, val1, val2);
    printList(head);

    // insert '101' into list before the value '1'
    SET(1, val3, int);
    SET(101, val4, int);
    head = insertBefore(head, val3, val4);
    printf("Insert %d before %d\n", *val4, *val3);
    printList(head);

    // delete '99' from the list
    SET(99, val5, int);
    deleteElement(head, val5);
    printf("Print after delete\n");
    printList(head);

    // search '5' in the list
    SET(87, val6, int);
    i = 0;
    if ((i = search(head, val6)) != -1)
        printf("%d found at %d\n", *val6, i);
    else
        printf("%d not in list\n", *val6);

    freeList(head);
#endif /* INTEGER_LIST */

//#define DOUBLE_LIST
#ifdef DOUBLE_LIST
    SET(1.0, headNum, double);
    Node* head = createNode(DOUBLE, headNum);

    for (int i = 1; i < 7; i++) {
        SET(i + 1, num, double);
        append(head, num);
    }
    printList(head);
#endif /* DOUBLE_LIST */

//#define CHAR_LIST
#ifdef CHAR_LIST
    SET('A', let, char);
    Node* head = createNode(CHAR, let);

    for (int i = 66; i < 75; i++) {
        SET(i, lets, char);
        append(head, lets);
    }
    printList(head);
#endif /* CHAR_LIST */

#define STRING_LIST
#ifdef STRING_LIST
    SET("hello", let1, char*);
    Node* head = createNode(STRING, let1);
    SET("you", let2, char*);
    append(head, let2);
    SET("u", let3, char*);
    append(head, let3);
    SET("ur name", let4, char*);
    append(head, let4);
    printList(head);
    printListReverse(head);

    SET("newString", let5, char*);
    insertAfter(head, let3, let5);
    printf("After insert after\n");
    printList(head);

    SET("newbeforeString", let6, char*);
    head = insertBefore(head, let1, let6);
    printf("After insert before\n");
    printList(head);

    SET("lol", let7, char*);
    printf("search: %d\n", search(head, let7));

    freeList(head);
#endif /* STRING_LIST */

    return 0;
}
