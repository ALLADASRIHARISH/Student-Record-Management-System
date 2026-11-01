#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "student.h"
int stud_save(void) {
    const Student *cur;
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) { perror("Could not open student.dat for writing"); return 0; }
    for (cur = head; cur != NULL; cur = cur->next) {
        if (strpbrk(cur->name, "\t\r\n") != NULL) {
            fprintf(stderr, "Cannot save a name containing tabs or newlines.\n");
            fclose(fp); return 0;
        }
        if (fprintf(fp, "%d\t%.6f\t%s\n", cur->roll, cur->percentage, cur->name) < 0) {
            perror("Error writing student.dat"); fclose(fp); return 0;
        }
    }
    if (fclose(fp) != 0) { perror("Error closing student.dat"); return 0; }
    return 1;
}
int stud_load(void) {
    FILE *fp = fopen(DATA_FILE, "r");
    char line[512];
    int loaded = 0;
    if (fp == NULL) {
        if (errno != ENOENT) perror("Could not open student.dat");
        return 0;
    }
    while (fgets(line, sizeof line, fp) != NULL) {
        int roll, fields;
        float percentage;
        char name[NAME_SIZE], extra;
        Student *node, *tail;
        fields = sscanf(line, "%d\t%f\t%99[^\r\n]%c", &roll, &percentage, name, &extra);
        if (fields < 3 || roll <= 0 || !isfinite(percentage) ||
            percentage < 0.0f || percentage > 100.0f || name[0] == '\0' ||
            stud_roll_exists(roll)) {
            fprintf(stderr, "Skipping invalid record in student.dat.\n"); continue;
        }
        node = malloc(sizeof *node);
        if (node == NULL) { fprintf(stderr, "Out of memory loading records.\n"); fclose(fp); return loaded; }
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
        loaded++;
    }
    if (ferror(fp)) perror("Error reading student.dat");
    fclose(fp);
    return loaded;
}
