CC =gcc
CFLAGS = -Wall -Werror -Wextra -c

SOURCE = flags.c s21_cat.c files.c
OBJECTS = $(SOURCE:.c=.o)
EXECUTABLE = CAT

all: $(OBJECTS)
	$(CC) $(OBJECTS)  -o $(EXECUTABLE)

rebuild: clean all

.o: .c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(EXECUTABLE)
	-rm *.o