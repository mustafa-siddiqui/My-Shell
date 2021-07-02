/**
 *  @file   linked_list.h
 *  @brief  Declarations of functions and structs used for
 *          implementing linked lists.
 *          => All values provided as arguments should be malloc'd beforehand
 *          because of arguments being pointers (basically passed by reference) <= 
 *  @brief  Mustafa Siddiqui
 *  @date   06/26/21
 */

#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

/*  
    NOTE:
    To see how the compiler will replace the macro with its definition, do:
        gcc -E <file-name> > macro_expansion.txt
    => better to redirect to a file if the code file includes other files
*/

/*
    Check if two pointers are of the same type or not. If they are not, they
    cannot be compared by dereferencing using the macro _ACCESS_VALUE.
*/
#define _TYPE_CHECK(ptr1, ptr2)                                                                                             \
    do {                                                                                                                    \
        if (!__builtin_types_compatible_p(typeof(*(ptr1)), typeof(*(ptr2)))) {                                              \
            fprintf(stderr, "Comparison with incompatible types at line %d in function %s()\n", __LINE__, __FUNCTION__);    \
            exit(EXIT_FAILURE);                                                                                             \
        }                                                                                                                   \
    } while (0)

/*
    Allocate memory for some specified data type;
*/
#define _ALLOC_MEM(type) (type*) malloc(sizeof(type))

/*
    => check if this is useful or not! <=
*/
#define _ASSIGN(val, type) (type*)val

/*
    Access value from void pointer by making use of typecasting.
*/
#define _ACCESS_VALUE(ptr, type) *((type*)ptr)

/*
    Compare values stored in locations pointed to by void pointers by making
    use of void pointers.
    => if used on strings, it will check if the pointers point to the same
    location rather than the strings having the same characters <=
    => use _STR_COMPARE for strings <=
*/
#define _COMPARE(val1, val2, type) ((*(type*)val1 != *(type*)val2) ? 1 : 0) 
#define _STR_COMPARE(str1, str2) ((strcmp(*(char**)str1, *(char**)str2) != 0) ? 1 : 0)

/*
    Data types available to store as data in the linked list.
    => structs are not supported as of now (each struct will require explicit
    support with current implementation) <=
*/
enum {
    INTEGER,
    DOUBLE,
    CHAR,
    STRING,
} typedef DATA_TYPES;

/*
    Struct holds some data element and a pointer to the next
    element in the linked list. Can use store either integer,
    double, char, or char* type variables as data.
*/
struct linkedListNode {
    DATA_TYPES dataType;
    void* value;
    struct linkedListNode* next;
} typedef Node;

static inline int compare(void* ptr1, void* ptr2, DATA_TYPES dataType);

/*
    Allocate memory for a node given the data type the user wants to store
    and store data in 'value' field. Sets 'next' pointer to NULL as default.
    Returns a pointer to that node.
*/
Node* createNode(DATA_TYPES dataType, void* val);

/* 
    Append value to the end of the list.
*/
Node* append(Node* head, void* value);

/*
    Insert value after some value/element in the list.
    'valueBeforeInsert' is the value in the list after which the new 
    value will be inserted.
*/
void insertAfter(Node* head, void* valueBeforeInsert, void* insertValue);

/*
    Insert value before some value/element in the list.
    'valueAfterInsert' is the value in the list before which the new
    value will be inserted.
    Returns Node* since the head of the list can be changed.
*/
Node* insertBefore(Node* head, void* valueAfterInsert, void* insertValue);

/*
    Delete element from list.
*/
void deleteElement(Node* head, void* valueToDelete);

/*
    Search for value in the list.
    Returns '-1' if value not found & the position/index of the value 
    in the list if found.
*/
int search(Node* head, void* valueToSearch);

/*
    Print all elements in the list.
*/
void printList(Node* head);

/*
    Print all elements in the list in reverse.
    Recursive function.
*/
void printListReverse(Node* head);

/*
    Free memory for all elements in the list.
*/
void freeList(Node* head);

#endif  /* _LINKED_LIST_H_ */