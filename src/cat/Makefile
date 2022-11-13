.PHONY: all, clean, rebuild, s21_cat , re

CC =gcc

FLAGS_DIR = flags
FILESDATA_DIR = ../common/filesData
FILE_DIR = ../common/file

INCLUDES = -I./$(FLAGS_DIR) -I./$(FILESDATA_DIR) -I./$(FILE_DIR) 

CFLAGS =  -Wall -Wextra -Werror -c

SOURCE = s21_cat.c $(wildcard $(FLAGS_DIR)/*.c) $(wildcard $(FILESDATA_DIR)/*.c) $(wildcard $(FILE_DIR)/*.c)
OBJECTS = $(SOURCE:.c=.o)



EXECUTABLE = s21_cat

.PHONY: s21_cat
s21_cat: all

.PHONY: all
all: $(OBJECTS)
	$(CC) $(INCLUDES) $(OBJECTS)  -o $(EXECUTABLE)

.PHONY: re
re: rebuild

.PHONY: rebuild
rebuild: clean all

%.o: %.c
	$(CC) $(LIBFLAGS) $(INCLUDES) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm $(EXECUTABLE)
	-rm $(OBJECTS)