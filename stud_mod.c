#include <stdio.h>
#include <string.h>
#include "student.h"
void stud_mod(void) {
    char search, field, name[NAME_SIZE];
    int roll, matches = 0;
    float percentage;
    Student *cur = NULL, *it;
    printf("\nR/r : Roll Number\nN/n : Name\nP/p : Percentage\n");
    if (!stud_read_choice("Enter Your Choice: ", &search)) return;
    if (search == 'R' || search == 'r') {
        if (!stud_read_int("Enter Roll Number: ", &roll)) return;
        cur = stud_find_roll(roll);
        if (cur == NULL) { printf("Record not found.\n"); return; }
    } else if (search == 'N' || search == 'n') {
        if (!stud_read_line("Enter Name to Search: ", name, sizeof name)) return;
        printf("\n%-10s %-30s %s\n", "Roll No", "Name", "Percentage");
        for (it = head; it != NULL; it = it->next) if (strcmp(it->name, name) == 0) {
            printf("%-10d %-30s %.2f\n", it->roll, it->name, it->percentage); matches++;
        }
        if (!matches) { printf("No matching records found.\n"); return; }
        if (!stud_read_int("Enter Roll Number of the record to modify: ", &roll)) return;
        cur = stud_find_roll(roll);
        if (cur == NULL || strcmp(cur->name, name) != 0) {
            printf("Roll number does not belong to the matching name.\n"); return;
        }
    } else if (search == 'P' || search == 'p') {
        if (!stud_read_float("Enter Percentage to Search (0-100): ", &percentage)) return;
        printf("\n%-10s %-30s %s\n", "Roll No", "Name", "Percentage");
        for (it = head; it != NULL; it = it->next) {
            float diff = it->percentage - percentage;
            if (diff < 0) diff = -diff;
            if (diff < 0.01f) {
                printf("%-10d %-30s %.2f\n", it->roll, it->name, it->percentage); matches++;
            }
        }
        if (!matches) { printf("No matching records found.\n"); return; }
        if (!stud_read_int("Enter Roll Number of the record to modify: ", &roll)) return;
        cur = stud_find_roll(roll);
        if (cur == NULL) { printf("Record not found.\n"); return; }
        {
            float diff = cur->percentage - percentage;
            if (diff < 0) diff = -diff;
            if (diff >= 0.01f) { printf("That record is not among the percentage matches.\n"); return; }
        }
    } else { printf("Invalid search choice. Select R, N, or P.\n"); return; }

    printf("\nSelected Record:\n"); stud_print_one(cur);
    printf("\nN/n : Modify Name\nP/p : Modify Percentage\n");
    if (!stud_read_choice("Enter Your Choice: ", &field)) return;
    if (field == 'N' || field == 'n') {
        if (!stud_read_line("Enter New Name: ", name, sizeof name)) return;
        if (name[0] == '\0') { printf("Name cannot be empty.\n"); return; }
        snprintf(cur->name, sizeof cur->name, "%s", name);
        printf("Name updated successfully.\n");
    } else if (field == 'P' || field == 'p') {
        if (!stud_read_float("Enter New Percentage (0-100): ", &percentage)) return;
        cur->percentage = percentage;
        printf("Percentage updated successfully.\n");
    } else printf("Invalid field choice. Select N or P.\n");
}
