CC =gcc
CFLAGS = -Wall -Wextra -c

SOURCE = flags.c s21_cat.c filesData.c file.c
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