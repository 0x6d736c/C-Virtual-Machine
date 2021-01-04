SRC = main.c
FLAGS = -Wall -Wextra -g -std=c11
CC = gcc

all:
	${CC} ${SRC} ${FLAGS} -o virMac