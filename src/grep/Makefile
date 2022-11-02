.PHONY: all, clean, rebuild, s21_cat, s21_grep

CC = gcc
#CFLAGS = -c -Wall -Werror -Wextra -lpcre
CFLAGS = -lpcre

SOURCES = s21_grep.c
OBJECTS = $(SOURCES:.c=.o)

EXECUTABLE = MAIN

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)


rebuild: clean all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm  *.o
	-rm EXECUTABLE
	-rm *.out