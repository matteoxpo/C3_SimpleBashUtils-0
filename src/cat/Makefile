CC =gcc

FLAGS_DIR = flags
FILESDATA_DIR = filesData
FILE_DIR = file

INCLUDES = -I./$(FLAGS_DIR) -I./$(FILESDATA_DIR) -I./$(FILE_DIR) 

CFLAGS = $(INCLUDES) -Wall -Wextra -Werror -c

SOURCE = s21_cat.c $(FLAGS_DIR)/*.c $(FILESDATA_DIR)/*.c $(FILE_DIR)/*.c
OBJECTS = $(SOURCE:.c=.o)

EXECUTABLE = CAT

all: $(OBJECTS)
	$(CC) $(OBJECTS)  -o $(EXECUTABLE)

rebuild: clean all

.o: .c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE)
	-rm $(OBJECTS)