.PHONY: all, clean, rebuild, s21_cat, s21_grep, re

CC = gcc
#CFLAGS = -c -Wall -Werror -Wextra -lpcre
CFLAGS = -lpcre

SOURCES = s21_grep.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = MAIN.out

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

re: rebuild

rebuild: clean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm  $(wildcard *.o)
	-rm $(wildcard *.out)