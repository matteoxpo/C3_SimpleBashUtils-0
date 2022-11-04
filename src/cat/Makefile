.PHONY: all, clean, rebuild, s21_cat, re

CC =gcc

FLAGS_DIR = flags
FILESDATA_DIR = filesData
FILE_DIR = ../common/file

INCLUDES = -I./$(FLAGS_DIR) -I./$(FILESDATA_DIR) -I./$(FILE_DIR) 

CFLAGS =  -Wall -Wextra -Werror -c

SOURCE = s21_cat.c $(wildcard $(FLAGS_DIR)/*.c) $(wildcard $(FILESDATA_DIR)/*.c) $(wildcard $(FILE_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)

EXECUTABLE = s21_cat

s21_cat: all

all: $(OBJECTS)
	$(CC) $(OBJECTS)  -o $(EXECUTABLE)

re: rebuild

rebuild: clean all

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE)
	-rm $(OBJECTS)