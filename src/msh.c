/**
 *  @file   msh.c
 *  @brief  Definitions of functions declared in msh.h and
 *          are used by the shell program.
 *  @author Mustafa Siddiqui
 *  @date   06/26/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     // fork(), execvp(), chdir(), pid_t
// -- //
#include <src/msh.h>

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

/* start a shell process */
int launchProcess(char** tokens) {
    pid_t pid, wait_pid = 0;
    int status = 0;

    // =0 -> returned to created child process
    // >0 -> returned to parent process
    // <0 -> creation of child unsuccessful
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Process creation failed.\n");
    }
    else if (pid == 0) {
        if (execvp(tokens[0], tokens) == -1)
            fprintf(stderr, "Failed to replace process image with new one.\n");
        exit(EXIT_FAILURE);
    }
    else {
        // wait till the process has exited or is killed by some signal
        do {
            wait_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/* execute built-in shell command or process */
int executeCommand(char** tokens) {
    // return if the user entered no command
    if (tokens[0] == NULL)
        return 1;
    
    // run built-in shell command if command matches any
    for (int i = 0; i < numBuiltIns(); i++) {
        if (strcmp(builtIns[i], tokens[0]) == 0)
            return ((*builtInFuncs[i])(tokens));
    }

    return launchProcess(tokens);
}

/* main shell loop */
void mshLoop(void) {
    int status = 0;

    do {
        printf("msh -> ");
        status = executeCommand(parseLine(readLine()));
    } while (status);
}

/* string array of built-in shell command names */
char* builtIns[] = {
    "cd",
    "help",
    "exit"
};

/* array of built-in command functions using fn pointers */
int (*builtInFuncs[]) (char**) = {
    &cd,
    &help,
    &exitShell
};

/* number of shell built-in commands */
int numBuiltIns() {
    return (sizeof(builtIns) / sizeof(char*));
}

/* change directory */
int cd(char** tokens) {
    if (tokens[1] == NULL) {
        fprintf(stderr, "Need location to change current directory to.\n");
        return -1;
    }

    // chdir() returns 0 on successful completion
    if (chdir(tokens[1]) != 0) {
        fprintf(stderr, "Error changing directory.\n");
        return -1;
    }
    
    return 1;
}

/* display info and built-in commands */
int help(char** tokens) {
    printf("Welcome to MyShell Help Page:\n");
    printf("Following commands are builtin:\n");
    for (int i = 0; i < numBuiltIns(); i++) {
        printf("%d. %s\n", i + 1, builtIns[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

/* exit shell */
int exitShell(char** tokens) {
    return EXIT_SUCCESS;
}
