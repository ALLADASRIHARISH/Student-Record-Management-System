# Student Record Management System

A menu-driven C project using a singly linked list and multiple source files.

## Features
- Add student with the smallest available positive roll number
- Prevent duplicate roll numbers
- Delete by roll number or name
- Display all records in a table
- Modify by roll number, name, or percentage; update name or percentage
- Save/load `student.dat`
- Sort by name or percentage
- Save and exit, or exit without saving current in-memory changes

## Files
- `main.c` — menu and program control
- `student.h` — shared structure and declarations
- `stud_add.c` — add
- `stud_del.c` — delete
- `stud_show.c` — display
- `stud_mod.c` — modify
- `stud_save.c` — save/load
- `stud_sort.c` — sorting
- `stud_utils.c` — validated input and shared helpers
- `Makefile` — build helper

## Compile on Ubuntu/Linux
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c stud_add.c stud_del.c stud_show.c stud_mod.c stud_save.c stud_sort.c stud_utils.c -o student -lm
./student
```
Or run `make` then `./student`.

## Data
`student.dat` is created in the current working directory. Each line contains `roll<TAB>percentage<TAB>name`. Choose `V` to save. Valid records are loaded when the program starts. Sorting is ascending; choose `V` to persist the sorted order.

## Assignment menu
`A` Add, `D` Delete, `S` Show, `M` Modify, `V` Save, `T` Sort, `E` Exit submenu.
