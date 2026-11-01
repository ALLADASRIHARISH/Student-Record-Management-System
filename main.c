#include <stdio.h>
#include <stdlib.h>
#include "student.h"
Student *head = NULL;

static void show_menu(void) {
    printf("\n**** STUDENT RECORD MENU ****\n\n");
    printf("A/a : Add New Record\nD/d : Delete a Record\nS/s : Show the List\n");
    printf("M/m : Modify a Record\nV/v : Save\nT/t : Sort the List\nE/e : Exit\n\n");
}
int main(void) {
    char choice;
    int loaded = stud_load();
    if (loaded > 0) printf("Loaded %d record(s) from %s.\n", loaded, DATA_FILE);
    else printf("No existing records loaded. Starting with an empty list.\n");

    for (;;) {
        show_menu();
        if (!stud_read_choice("Enter Your Choice: ", &choice)) {
            printf("\nInput ended. Exiting without saving changes.\n");
            stud_free_all();
            return 0;
        }
        switch (choice) {
            case 'A': case 'a': stud_add(); break;
            case 'D': case 'd': stud_del(); break;
            case 'S': case 's': stud_show(); break;
            case 'M': case 'm': stud_mod(); break;
            case 'V': case 'v':
                if (stud_save()) printf("Records saved successfully to %s.\n", DATA_FILE);
                else printf("Save failed. Check file permissions and disk space.\n");
                break;
            case 'T': case 't': stud_sort(); break;
            case 'E': case 'e': {
                char exit_choice;
                printf("\nS/s : Save and Exit\nE/e : Exit Without Saving\n\n");
                if (!stud_read_choice("Enter Your Choice: ", &exit_choice)) {
                    stud_free_all(); return 0;
                }
                if (exit_choice == 'S' || exit_choice == 's') {
                    if (stud_save()) {
                        printf("Records saved. Goodbye!\n");
                        stud_free_all(); return 0;
                    }
                    printf("Save failed; returning to the main menu so you can retry.\n");
                } else if (exit_choice == 'E' || exit_choice == 'e') {
                    printf("Exiting without saving current changes.\n");
                    stud_free_all(); return 0;
                } else printf("Invalid exit choice. Returning to the main menu.\n");
                break;
            }
            default: printf("Invalid choice. Please enter A, D, S, M, V, T, or E.\n");
        }
    }
}
