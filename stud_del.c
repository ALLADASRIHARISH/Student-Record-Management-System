#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
static void delete_roll(int roll) {
    Student *cur = head, *prev = NULL;
    while (cur != NULL && cur->roll != roll) { prev = cur; cur = cur->next; }
    if (cur == NULL) { printf("Record with roll number %d not found.\n", roll); return; }
    if (prev == NULL) head = cur->next; else prev->next = cur->next;
    free(cur);
    printf("Record deleted successfully.\n");
}
void stud_del(void) {
    char choice, name[NAME_SIZE];
    int roll, matches = 0;
    Student *cur;
    printf("\nR/r : Delete using Roll Number\nN/n : Delete using Name\n");
    if (!stud_read_choice("Enter Your Choice: ", &choice)) return;
    if (choice == 'R' || choice == 'r') {
        if (stud_read_int("Enter Roll Number to Delete: ", &roll)) delete_roll(roll);
    } else if (choice == 'N' || choice == 'n') {
        if (!stud_read_line("Enter Student Name: ", name, sizeof name)) return;
        printf("\n%-10s %-30s %s\n", "Roll No", "Name", "Percentage");
        printf("--------------------------------------------------------\n");
        for (cur = head; cur != NULL; cur = cur->next) {
            if (strcmp(cur->name, name) == 0) {
                printf("%-10d %-30s %.2f\n", cur->roll, cur->name, cur->percentage);
                matches++;
            }
        }
        if (matches == 0) { printf("No records found with that name.\n"); return; }
        if (!stud_read_int("Enter the Roll Number of the record to delete: ", &roll)) return;
        cur = stud_find_roll(roll);
        if (cur == NULL || strcmp(cur->name, name) != 0) {
            printf("That roll number is not among the matching records.\n"); return;
        }
        delete_roll(roll);
    } else printf("Invalid choice. Select R or N.\n");
}
