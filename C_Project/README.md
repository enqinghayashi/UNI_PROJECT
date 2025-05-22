# Mini-Language (ML) to C Transpiler (`runml`)

## 📖 Project Description
This project features `runml`, a command-line tool written in C11. Its core function is to process a custom mini-language (ml), which is designed for basic real-number operations and function calls. The `runml` tool transpiles `ml` source code into equivalent C11 code, then leverages a system C compiler (like `gcc` or `clang`) to compile the generated C code, and finally executes the resulting program. This project demonstrates key concepts in language processing, including lexical analysis (tokenization), parsing, code generation, and interaction with system tools.

---

## ✨ Key Features
-   **Transpilation**: Converts programs written in the mini-language (`.ml` files) into C11 source code.
-   **Automated Compilation**: Invokes the system's C compiler to build an executable from the transpiled C code.
-   **Execution**: Runs the compiled program, with support for passing command-line arguments to the `ml` program.
-   **Basic Syntax Validation**: Performs initial checks on the `ml` source code for syntactic correctness.

---

## ⚙️ Technologies Used
-   **Primary Language**: C11
-   **Compiler for `runml`**: Standard C compiler (e.g., GCC, Clang)
-   **Compiler for Transpiled Code**: System C compiler (e.g., GCC, Clang)

---

## 🚀 Setup and Usage

### 1. Prerequisites
-   A C11 compatible compiler (e.g., `gcc` or `clang`) must be installed and accessible in your system's PATH.

### 2. Compile `runml`
Navigate to the `ML_Transpiler_C` directory (or the current project directory) in your terminal and compile the `runml.c` source file:
```bash
cc -std=c11 -Wall -Werror -o runml runml.c
```
This command creates an executable file named `runml` in the current directory.

### 3. Run an `ml` Program
Once `runml` is compiled, you can use it to transpile, compile, and execute your `.ml` programs.

**Syntax:**
```bash
./runml your_program.ml [argument1 argument2 ...]
```

**Process:**
1.  `runml` reads and validates `your_program.ml`.
2.  If valid, it transpiles the `ml` code into an intermediate C source file.
3.  It then compiles this C file using the system compiler to produce an executable.
4.  Finally, it executes this program, passing any additional `[argument1 argument2 ...]` as command-line arguments to your `ml` program's `main` function.

---

## 📝 Example

Suppose you have an `ml` file named `example.ml`.

**Step 1: Compile the `runml` transpiler (if not already done)**
```bash
cc -std=c11 -Wall -Werror -o runml runml.c
```

**Step 2: Run your `ml` program using `runml`**
```bash
./runml example.ml
```
If `example.ml` is designed to accept command-line arguments (e.g., two numbers to add):
```bash
./runml example.ml 10 25
```

---

## 📄 License
This project is licensed under the MIT License. See the main [LICENSE](../../LICENSE) file for details.

