# Pipex

The **Pipex** project is a simplified re-implementation of the shell's piping functionality. It replicates the behavior of the shell command `cmd1 | cmd2`, allowing the user to pass data from one command to another through pipes. This project is a part of the **42 School curriculum** and focuses on process creation, inter-process communication, and file descriptor management.

## Table of Contents
- [Project Description](#project-description)
- [Features](#features)
- [Directory Structure](#directory-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Project Rules](#project-rules)
- [Authors](#authors)

## Project Description

The **Pipex** program replicates the behavior of shell piping by taking the following format:

```bash
./pipex file1 cmd1 cmd2 file2
```

This command redirects the output of cmd1 to the input of cmd2 through a pipe, with file1 serving as the input to cmd1 and file2 as the output from cmd2.
Problem Breakdown:

    file1 is the input file, whose content is sent to the first command (cmd1).
    The output of cmd1 is piped as the input to cmd2.
    The output of cmd2 is then written to file2.

The project demonstrates:

    File I/O redirection.
    Creating child processes using fork().
    Piping data between processes using pipe().
    Executing commands using execve().
    Properly handling errors and memory management.

## Features

    Handles simple pipes (cmd1 | cmd2).
    Reads from an input file and writes to an output file.
    Manages environment paths to locate executables.
    Handles edge cases such as invalid commands, permission errors, and non-existent files.

## Directory Structure

```plaintext

.
├── Makefile
├── includes
│   └── pipex.h
├── src
│   ├── parse_args.c
│   ├── get_path_and_env.c
│   ├── utils.c
│   ├── main.c
│   ├── the_fam.c
│   └── error_free.c
├── libft
├── test.txt
└── README.md
```

Makefile: Compiles and links the program.
includes/: Contains the pipex.h header file, which defines function prototypes and shared structs.
src/: Contains the core source files for parsing arguments, managing the pipe, and handling errors.
libft/: The Libft library (custom C library with utility functions).
test.txt: Example input file for testing.

## Installation

To compile the project, run the following commands:

```bash
git clone https://github.com/yourusername/pipex.git
cd pipex
make
```

This will produce the executable pipex.

## Usage

The basic usage of the program is as follows:

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Where:

infile: The file to be used as input.
cmd1: The first command to be executed, which reads from the input file.
cmd2: The second command, which takes the output of cmd1 as input.
outfile: The file where the final output is written.

Example:

```bash
./pipex input.txt "ls -l" "grep pipex" output.txt
```

In this example:

input.txt: Input file (not used in this specific case as ls -l lists files).
"ls -l": Lists files in the current directory.
"grep pipex": Filters the output of ls -l for lines containing "pipex".
output.txt: The filtered result is written to this file.

## Project Rules

Global variables are forbidden.
The program must properly handle errors (e.g., permission denied, command not found).
The use of external libraries other than Libft is prohibited.
The project must be implemented in C and comply with the 42 School coding norms.

## Authors

- **Ashley Fletcher** - *Developer* - [GitHub Profile](https://github.com/ashleyfletcher76)
