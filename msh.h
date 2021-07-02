/**
 *  @file   my_shell.h
 *  @brief  Declarations of macros and functions used by the
 *          shell program.
 *  @author Mustafa Siddiqui
 *  @date   06/26/2021
 */

#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#define MEMALLOC_ERROR_MSG  ("Error allocating memory at line %d in function %s() in %s\n")
#define BUFFER_LEN          (25)
#define NUM_ARGS            (3)
#define WHITESPACE_DELIM    (" \t\r\n\a")

/*
    Checks if memory allocation was successful or not.
    Returns 1 if successful allocation, 0 if not.
    (extern inline makes the fn used for inlining only => almost as if a macro)
*/
extern inline int memAllocCheck(void* ptr);

/*
    Reads a line from the shell entered by the user and
    stores in a string which is dynamically sized according
    to the size of the characters entered.
*/
char* readLine(void);

/*
    Parse a line read from the shell and returns a char* array
    with the line split based on whitespace.
*/
char** parseLine(char* line);

#endif  /* _MY_SHELL_H_ */