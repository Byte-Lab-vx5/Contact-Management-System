
# Contact Management System in C

A simple, menu-driven Contact Management System built with the C programming language. This project is part of my journey to improve my C programming skills and build practical projects.

## About the Project

The Contact Management System allows users to manage contact information through a command-line interface.

Each contact contains the following information:
- **Name**
- **Email**
- **Phone Number**

Contact records are stored in a binary file named `contact.dat`, allowing the program to save contact information between runs.

## Features

### Implemented
- Add new contacts
- Search for contacts by name
- Update existing contact information
- Basic input validation

### Planned Features
- Display all contacts
- Sort contacts
- Delete contacts
- Improve input validation and error handling

## Requirements

To compile and run this project, you need:

- A C compiler, such as GCC
- A terminal or command-line environment
- Basic familiarity with running C programs

## How to Compile and Run

### Linux

Compile the program:

```bash
gcc contact_system.c -o contact_system
```

Run it:

```bash
./contact_system
```

### Windows (MinGW GCC)

Compile the program:

```bash
gcc contact_system.c -o contact_system.exe
```

Run it:

```bash
contact_system.exe
```

## Data Storage

The program stores contact records in a binary file called `contact.dat`.

The file is created when contacts are saved. Since the program stores C structures directly in binary format, the file may not be portable across different compilers or systems.

## Concepts Practiced

This project helps me practise:

- Structures (`struct`)
- Functions
- Arrays and strings
- Loops and conditional statements
- Dynamic memory allocation
- File handling (`fopen`, `fread`, `fwrite`, `fclose`)
- String comparison using `strcmp()`
- Input validation
- Basic program organization

## Current Status

This project is a work in progress. I am building it step by step as I strengthen my understanding of C programming, especially strings, file handling, input validation, and memory management.

More features and improvements will be added as development continues.

## Future Improvements

- Strengthen input validation
- Handle file errors more reliably
- Improve the user interface
- Complete the sorting, displaying, and deleting features
- Improve the overall code structure

## Author

A C programming learner working on practical projects to develop stronger programming skills and progress toward systems programming.

---

**Language:** C  
**Project Type:** Command-line application  
**Status:** In development

