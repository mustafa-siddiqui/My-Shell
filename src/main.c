/**
 *  @file   main.c
 *  @brief  The driver code for the shell program.
 *          => msh -> My Shell <=
 *  @author Mustafa Siddiqui
 *  @date   07/02/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
// -- //
#include <src/msh.h>

int main(void) {
    // run shell loop
    mshLoop();

    return 0;
}