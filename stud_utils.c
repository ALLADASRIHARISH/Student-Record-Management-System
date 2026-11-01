#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "student.h"
int stud_read_line(const char *prompt, char *buffer, size_t size) {
    size_t len; int ch;
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) return 0;
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    else while ((ch = getchar()) != '\n' && ch != EOF) { }
    return 1;
}
int stud_read_choice(const char *prompt, char *choice) {
    char line[64];
    if (!stud_read_line(prompt, line, sizeof line)) return 0;
    *choice = line[0] == '\0' ? '\0' : line[0];
    return 1;
}
int stud_read_int(const char *prompt, int *value) {
    char line[128], *end; long parsed;
    for (;;) {
        if (!stud_read_line(prompt, line, sizeof line)) return 0;
        errno = 0; parsed = strtol(line, &end, 10);
        if (end == line) { printf("Please enter a valid integer.\n"); continue; }
        while (isspace((unsigned char)*end)) end++;
        if (*end != '\0' || errno == ERANGE || parsed < -2147483647L - 1L || parsed > 2147483647L) {
            printf("Invalid integer. Please try again.\n"); continue;
        }
        *value = (int)parsed; return 1;
    }
}
int stud_read_float(const char *prompt, float *value) {
    char line[128], *end; float parsed;
    for (;;) {
        if (!stud_read_line(prompt, line, sizeof line)) return 0;
        errno = 0; parsed = strtof(line, &end);
        if (end == line) { printf("Please enter a valid number.\n"); continue; }
        while (isspace((unsigned char)*end)) end++;
        if (*end != '\0' || errno == ERANGE || !isfinite(parsed) || parsed < 0.0f || parsed > 100.0f) {
            printf("Percentage must be a number from 0 to 100.\n"); continue;
        }
        *value = parsed; return 1;
    }
}
Student *stud_find_roll(int roll) {
    Student *cur = head;
    while (cur != NULL) { if (cur->roll == roll) return cur; cur = cur->next; }
    return NULL;
}
int stud_roll_exists(int roll) { return stud_find_roll(roll) != NULL; }
int stud_next_roll(void) {
    int candidate = 1;
    while (stud_roll_exists(candidate)) {
        if (candidate == 2147483647) return -1;
        candidate++;
    }
    return candidate;
}
void stud_print_one(const Student *s) {
    if (s == NULL) return;
    printf("Roll Number : %d\nName        : %s\nPercentage  : %.2f\n", s->roll, s->name, s->percentage);
}
void stud_free_all(void) {
    Student *cur = head;
    while (cur != NULL) { Student *next = cur->next; free(cur); cur = next; }
    head = NULL;
}
