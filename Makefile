# compiler
CC = gcc

# compiler flags
CCFLAGS = -Wall

# add /Shell dir to include path
# replace space in dir name with '\ '
# workaround for make not working with dirs with spaces in names
INC = -I${shell pwd | sed 's/ /\\ /g'}

# files to be included
FILES = src/main.c src/msh.c src/linked_list.c

all:
	${CC} ${CCFLAGS} ${INC} ${FILES} -o msh

clean:
	rm -rf msh

debug:
	${CC} ${CCFLAGS} ${INC} ${FILES} -g -o msh-d

Debug-clean:
	rm -rf msh-d

