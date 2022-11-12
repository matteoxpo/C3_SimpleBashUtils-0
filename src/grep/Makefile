.PHONY: all, clean, rebuild, s21_cat , re

CC =gcc

FILESDATA_DIR = ../common/filesData
FILE_DIR = ../common/file

INCLUDES =  -I./$(FILESDATA_DIR) -I./$(FILE_DIR) 

CFLAGS =  -Wall -Wextra -Werror -c

LIBFLAGS = -lpcre

SOURCE = s21_grep.c $(wildcard $(FILESDATA_DIR)/*.c) $(wildcard $(FILE_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)



EXECUTABLE = s21_grep

.PHONY: s21_grep
s21_grep: all

.PHONY: all
all: $(OBJECTS)
	$(CC) $(INCLUDES) $(OBJECTS) -o $(EXECUTABLE) $(LIBFLAGS) 

.PHONY: re
re: rebuild

.PHONY: rebuild
rebuild: clean all

%.o: %.c
	$(CC)  $(INCLUDES) $(CFLAGS) $< -o $@ $(LIBFLAGS)

.PHONY: clean
clean:
	-rm $(EXECUTABLE)
	-rm $(OBJECTS)