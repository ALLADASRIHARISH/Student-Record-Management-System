#include <stdio.h>
#include "student.h"
void stud_show(void) {
    const Student *cur = head;
    int count = 0;
    if (cur == NULL) { printf("No student records available.\n"); return; }
    printf("\n---------------------------------------------------------------\n");
    printf("%-10s %-30s %s\n", "Roll No", "Name", "Percentage");
    printf("---------------------------------------------------------------\n");
    while (cur != NULL) {
        printf("%-10d %-30s %.2f\n", cur->roll, cur->name, cur->percentage);
        cur = cur->next; count++;
    }
    printf("---------------------------------------------------------------\nTotal records: %d\n", count);
}
