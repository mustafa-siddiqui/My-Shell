# compiler
CC = gcc

# compiler flags
CCFLAGS = -Wall

# files to be included
FILES = main.c msh.c linked_list.c

all:
	${CC} ${CCFLAGS} ${FILES} -o msh

clean:
	rm -rf msh

debug:
	${CC} ${CCFLAGS} ${FILES} -g -o msh-d

Debug-clean:
	rm -rf msh-d

