#ifndef STUDENT_H
#define STUDENT_H
#include <stdio.h>
#define NAME_SIZE 100
#define DATA_FILE "student.dat"
typedef struct student {
    int roll;
    char name[NAME_SIZE];
    float percentage;
    struct student *next;
} Student;
extern Student *head;
void stud_add(void);
void stud_del(void);
void stud_show(void);
void stud_mod(void);
int stud_save(void);
int stud_load(void);
void stud_sort(void);
Student *stud_find_roll(int roll);
void stud_free_all(void);
int stud_read_int(const char *prompt, int *value);
int stud_read_float(const char *prompt, float *value);
int stud_read_line(const char *prompt, char *buffer, size_t size);
int stud_read_choice(const char *prompt, char *choice);
void stud_print_one(const Student *student);
int stud_roll_exists(int roll);
int stud_next_roll(void);
#endif
