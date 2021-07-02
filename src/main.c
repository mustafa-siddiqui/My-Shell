/**
 *  @file   main.c
 *  @brief  The driver code for the shell program.
 *  @author Mustafa Siddiqui
 *  @date   07/02/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// -- //
#include "linked_list.h"
#include "msh.h"

/*
    Helpful macro to declare and set value for variable given
    the datatype. ** uses pointers, not basic variables **
    => requires assert.h to check memory allocation <=
*/
#define SET(val, var, type) type* var = _ALLOC_MEM(type);   \
                            assert(var);                    \
                            *var = val

int main(void) {
    char** tokens = parseLine(readLine());
    int i = 0;
    while (tokens[i] != NULL) {
        printf("%s\n", tokens[i]);
        i++;
    }

    return 0;
}