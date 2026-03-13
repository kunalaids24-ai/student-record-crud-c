# Student Record Management System (C)

A console-based **Student Record CRUD** application written in C language.  
It demonstrates full **Create, Read, Update, Delete** operations with permanent storage using binary files.

## Features

- Add new student records (ID, Name, Age, Marks)
- View all saved student records in a neat table format
- Update any student's details using their ID
- Delete a student record by ID
- Data is stored permanently in a binary file (`students.dat`)
- Simple menu-driven interface

## Technologies / Concepts Used

- C programming language
- Structures (`struct Student`)
- Binary file handling (`fread`, `fwrite`, `fseek`, `remove`, `rename`)
- File-based persistent storage (no database needed)
- Modular functions + menu-driven program flow
- Switch-case and loop control

## How to Compile and Run

```bash
# Compile the program
gcc main.c -o student

# Run the program
./student          # Linux / macOS
student.exe        # Windows (if compiled with MinGW / Dev-C++)