/**
 *  @file   my_shell.c
 *  @brief  Definitions of functions declared in msh.h and
 *          are used by the shell program.
 *  @author Mustafa Siddiqui
 *  @date   06/26/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// -- //
#include "msh.h"

/* check for NULL */
int memAllocCheck(void* ptr) {
    return (ptr) ? 1 : 0;
}

/* read a line from the shell */
char* readLine(void) {
    int bufferSize = BUFFER_LEN;
    int i = 0;
    int c = 0;

    char* buffer = (char*) malloc(bufferSize * sizeof(char));
    if (!memAllocCheck(buffer)) {
        fprintf(stderr, MEMALLOC_ERROR_MSG, __LINE__, __FUNCTION__, __FILE__);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // read a single char from stdin
        c = getchar();

        // return if new line char or end of file
        if (c == EOF || c == (int)'\n') {
            buffer[i++] = '\0';
            return buffer;
        }
        else {
            buffer[i++] = (char)c;
        }

        // reallocate memory for buffer if current size not adequate
        if (i >= bufferSize) {
            bufferSize += BUFFER_LEN;
            buffer = (char*) realloc(buffer, bufferSize * sizeof(char));
            if (!memAllocCheck(buffer)) {
                fprintf(stderr, MEMALLOC_ERROR_MSG, __LINE__, __FUNCTION__, __FILE__);
                exit(EXIT_FAILURE);
            }
        }
    }
}

/* parse line according to whitespace */
char** parseLine(char* line) {
    int numToken = NUM_ARGS;
    char* delim = WHITESPACE_DELIM;

    // allocate memory to store tokens
    int i = 0;
    char** tokens = (char**) malloc(numToken * sizeof(char*));
    if (!memAllocCheck(tokens)) {
        fprintf(stderr, MEMALLOC_ERROR_MSG, __LINE__, __FUNCTION__, __FILE__);
        exit(EXIT_FAILURE);
    }

    // parse line with whitespace characters as delimiters
    char* token = strtok(line, delim);
    while (token != NULL) {
        tokens[i++] = token;

        // reallocate memory if more needed
        if (i >= numToken) {
            numToken += NUM_ARGS;
            tokens = (char**) realloc(tokens, numToken * sizeof(char*));
            if (!memAllocCheck(tokens)) {
                fprintf(stderr, MEMALLOC_ERROR_MSG, __LINE__, __FUNCTION__, __FILE__);
                exit(EXIT_FAILURE);
            }
        }

        // get next token
        token = strtok(NULL, delim);
    }

    // store last token as NULL
    tokens[i] = NULL;
    return tokens;
}
