# C Project: runml - Mini-Language Transpiler

## Project Description
We're all familiar with higher-level programming languages like Python, Java, and C. But this project focuses on a mini-language (ml) designed for basic real-number operations and function calls. The goal is to write a C11 program, `runml`, that transpiles ml code to C, compiles the generated C code, and executes it.

## Features
- Transpiles ml programs to C11 code.
- Uses a system compiler to compile the generated C code.
- Executes the compiled program with command-line arguments.

## Steps to Use

1. **Compile the `runml` program:**
   Use the following command to compile the `runml.c` file:
   ```bash
   cc -std=c11 -Wall -Werror -o runml runml.c

This will create an executable named runml.

Run the runml program with an .ml file: Once the runml program is compiled, you can run it by passing an ml program file as an argument. For example:
./runml sample.ml
runml will:
Check for syntax errors in the sample.ml program.
Transpile the valid ml code to C code.
Compile the transpiled C code.
Execute the compiled C program.
Optional: Pass additional arguments to the ml program: If your ml program requires command-line arguments, you can pass them after the .ml file:
./runml sample.ml arg1 arg2 ...
## Example
Suppose you have an ml file named example.ml, you would follow these steps to compile and run it:
# Step 1: Compile the runml program
cc -std=c11 -Wall -Werror -o runml runml.c

# Step 2: Run the ml program
./runml example.ml

