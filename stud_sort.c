#include <stdio.h>
#include <string.h>
#include "student.h"
static void swap_data(Student *a, Student *b) {
    int roll = a->roll;
    float percentage = a->percentage;
    char name[NAME_SIZE];
    snprintf(name, sizeof name, "%s", a->name);
    a->roll = b->roll; a->percentage = b->percentage;
    snprintf(a->name, sizeof a->name, "%s", b->name);
    b->roll = roll; b->percentage = percentage;
    snprintf(b->name, sizeof b->name, "%s", name);
}
void stud_sort(void) {
    char choice;
    int swapped;
    if (head == NULL || head->next == NULL) { printf("At least two records are required to sort.\n"); return; }
    printf("\nN/n : Sort by Name\nP/p : Sort by Percentage\n");
    if (!stud_read_choice("Enter Your Choice: ", &choice)) return;
    if (choice != 'N' && choice != 'n' && choice != 'P' && choice != 'p') {
        printf("Invalid sort choice. Select N or P.\n"); return;
    }
    do {
        Student *cur = head;
        swapped = 0;
        while (cur->next != NULL) {
            int change = (choice == 'N' || choice == 'n')
                ? strcmp(cur->name, cur->next->name) > 0
                : cur->percentage > cur->next->percentage;
            if (change) { swap_data(cur, cur->next); swapped = 1; }
            cur = cur->next;
        }
    } while (swapped);
    printf("Records sorted in ascending order. Select V to save the sorted order.\n");
}
