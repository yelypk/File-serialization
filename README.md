# Student List (serialization.c)

A small console application in C for storing a list of students in a doubly linked list with saving/loading to a text file.

## Features
- Adding and deleting students (by first and last name).
- Printing the list to the console.
- Saving to the `data.txt` file and loading at startup.
- Input validation (numbers and strings, prohibition of the `|` symbol).

## Data structures
- `struct Student` — first name, last name, middle name, `struct Date {year, month, day}`, group, gender (`enum Sex { male, female }`).
- Data is stored in a doubly linked list `LList`.

##Application menu
- Print list of students
- Add student
- Delete student
- Exit (saving to data.txt)
