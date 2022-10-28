.PHONY: all, clean, rebuild, s21_cat, s21_grep

CC = gcc
CFLAGS = -c -Wall -Werror -Wextra

COMMONPATH = /common
CATPATH = /cat
GREPPATH = /grep

SRCCOMMON = common.c
OBJCOMMON = $(SOURCES:.c=.o)

EXECUTABLE = MAIN

all: $(OBJECTS)
	$(CC) $(BUILD_PATH)$(OBJECTS) -o $(BUILD_PATH)$(EXECUTABLE) $(GLFLAGS)
	$(BUILD_PATH)$(EXECUTABLE)


rebuild: clean all

%.o: %.c
	$(CC) $(CFLAGS) $< -o $(BUILD_PATH)$@

clean:
	-rm  $(BUILD_PATH)*