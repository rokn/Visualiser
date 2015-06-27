#OBJS specifies which files to compile
OBJS = main.c List.c parser.c

#CC specifies which compiler we're using
CC = gcc

#error log
ERROR_LOG = log.txt

#obj name for the name of the exe
OBJ_NAME = program

# this is the compile line

all : $(OBJS) 
	$(CC) $(OBJS) -w -o $(OBJ_NAME) 2> $(ERROR_LOG) && ./$(OBJ_NAME)