CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS = -lm
TARGET = student
SOURCES = main.c stud_add.c stud_del.c stud_show.c stud_mod.c stud_save.c stud_sort.c stud_utils.c

.PHONY: all clean
all: $(TARGET)
$(TARGET): $(SOURCES) student.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDLIBS)
clean:
	rm -f $(TARGET)
