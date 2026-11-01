#include <stdio.h>
#include <stdlib.h>
#include "student.h"
void stud_add(void) {
    Student *node, *tail;
    char name[NAME_SIZE];
    float percentage;
    int roll;
    if (!stud_read_line("Enter Student Name: ", name, sizeof name)) return;
    if (name[0] == '\0') { printf("Name cannot be empty.\n"); return; }
    if (!stud_read_float("Enter Percentage (0-100): ", &percentage)) return;
    roll = stud_next_roll();
    if (roll <= 0) { printf("Could not allocate a roll number.\n"); return; }
    node = malloc(sizeof *node);
    if (node == NULL) { printf("Memory allocation failed.\n"); return; }
    node->roll = roll;
    snprintf(node->name, sizeof node->name, "%s", name);
    node->percentage = percentage;
    node->next = NULL;
    if (head == NULL) head = node;
    else {
        tail = head;
        while (tail->next != NULL) tail = tail->next;
        tail->next = node;
    }
    printf("Record added successfully. Assigned Roll Number: %d\n", roll);
}
