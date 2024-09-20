#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 100

/**
 * Structure to represent a parsed ml statement.
 */
typedef struct {
    char* type;                // "function", "assignment", "print", "return", "call"
    char content[MAX_LINE_LENGTH]; // The content of the statement
    int is_indented;           // 1 if the statement is indented (belongs to a function), 0 otherwise
} Statement;

/**
 * Trims leading and trailing whitespace from a string.
 * @param str The string to trim.
 */
void trim(char* str) {
    char* start = str;
    char* end;

    // Trim leading spaces
    while (isspace((unsigned char)*start)) start++;

    // If all characters are spaces
    if (*start == 0) {
        *str = 0;
        return;
    }

    // Trim trailing spaces
    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';

    // Shift trimmed string back to the original buffer if necessary
    if (start != str) {
        memmove(str, start, end - start + 2); // +1 for '\0', +1 since end points to last character
    }
}

/**
 * Parses the ml file and extracts statements.
 * @param filename The name of the ml file to parse.
 * @param statements Pointer to an array of Statement pointers.
 * @return The number of statements parsed, or -1 on error.
 */
int parseml(char* filename, Statement** statements) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int count = 0;
    size_t capacity = INITIAL_CAPACITY;

    *statements = malloc(sizeof(Statement) * capacity);
    if (!*statements) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    while (fgets(line, sizeof(line), file)) {
        char original_line[MAX_LINE_LENGTH];
        strcpy(original_line, line); // Keep original line for indentation check

        trim(line);
        if (line[0] == '#' || strlen(line) == 0) continue; // Skip comments and empty lines

        // Determine if the original line was indented
        int is_indented = 0;
        if (original_line[0] == ' ' || original_line[0] == '\t') {
            is_indented = 1;
        }

        Statement* current = &((*statements)[count]);

        // Determine the type of statement
        if (strstr(line, "<-") != NULL) {
            current->type = "assignment";
        } else if (strncmp(line, "print ", 6) == 0) {
            current->type = "print";
        } else if (strncmp(line, "return ", 7) == 0) {
            current->type = "return";
        } else if (strncmp(line, "function ", 9) == 0) {
            current->type = "function";
        } else if (strstr(line, "(") != NULL && strstr(line, ")") != NULL) {
            current->type = "call";
        } else {
            fprintf(stderr, "Syntax error in line: %s\n", line);
            free(*statements);
            fclose(file);
            return -1;
        }

        strcpy(current->content, line);
        current->is_indented = is_indented;
        count++;

        // Dynamically resize the statements array if needed
        if (count == capacity) {
            capacity *= 2;
            Statement* temp = realloc(*statements, sizeof(Statement) * capacity);
            if (!temp) {
                perror("Memory reallocation failed");
                free(*statements);
                fclose(file);
                return -1;
            }
            *statements = temp;
        }
    }

    fclose(file);
    return count;
}

/**
 * Generates C code from parsed statements.
 * @param statements The array of parsed statements.
 * @param numStatements The number of statements.
 * @param outputFilename The name of the output C file.
 * @return 0 on success, -1 on error.
 */
int generateCCode(Statement* statements, int numStatements, char* outputFilename) {
    FILE* file = fopen(outputFilename, "w");
    if (!file) {
        perror("Failed to open output file");
        return -1;
    }
    fprintf(file, "#include <stdio.h>\n\n");

    // Part 1: Global Variable Declarations (only assignments outside functions)
    for (int i = 0; i < numStatements; i++) {
        if (strcmp(statements[i].type, "function") == 0) {
            continue;
        }

        if (strcmp(statements[i].type, "assignment") == 0 && statements[i].is_indented == 0) {
            // Handle global assignment statements
            char temp[MAX_LINE_LENGTH];
            strcpy(temp, statements[i].content);
            char* var = strtok(temp, "<-");
            if (var == NULL) continue; // Safety check
            trim(var);
            fprintf(file, "double %s;\n", var);
        }
    }
    fprintf(file, "\n");

    // Part 2: Function Definitions
    for (int i = 0; i < numStatements; i++) {
        if (strcmp(statements[i].type, "function") == 0) {
            char funcDef[MAX_LINE_LENGTH];
            strcpy(funcDef, statements[i].content);

            // Remove "function" keyword and extract function name and parameters
            strtok(funcDef, " "); // "function"
            char* funcName = strtok(NULL, " "); // Function name
            if (funcName == NULL) {
                fprintf(stderr, "Function name missing in statement: %s\n", statements[i].content);
                continue;
            }

            fprintf(file, "double %s(", funcName);

            // Collect function parameters
            char* param;
            int first = 1;
            while ((param = strtok(NULL, " ")) != NULL) {
                if (!first) {
                    fprintf(file, ", ");
                }
                fprintf(file, "double %s", param);
                first = 0;
            }
            fprintf(file, ") {\n");

            // Process function body
            int funcBodyStart = i + 1;
            int funcBodyEnd = funcBodyStart;
            while (funcBodyEnd < numStatements && statements[funcBodyEnd].is_indented == 1) {
                funcBodyEnd++;
            }

            // Collect all assigned variables to declare them locally
            char localVars[100][MAX_LINE_LENGTH];
            int localVarCount = 0;
            for (int j = funcBodyStart; j < funcBodyEnd; j++) {
                if (strcmp(statements[j].type, "assignment") == 0) {
                    char tempAssign[MAX_LINE_LENGTH];
                    strcpy(tempAssign, statements[j].content);
                    char* varAssign = strtok(tempAssign, "<-");
                    if (varAssign != NULL) {
                        trim(varAssign);
                        // Check if already declared
                        int alreadyDeclared = 0;
                        for (int k = 0; k < localVarCount; k++) {
                            if (strcmp(localVars[k], varAssign) == 0) {
                                alreadyDeclared = 1;
                                break;
                            }
                        }
                        if (!alreadyDeclared) {
                            strcpy(localVars[localVarCount++], varAssign);
                        }
                    }
                }
            }

            // Declare local variables
            for (int j = 0; j < localVarCount; j++) {
                fprintf(file, "    double %s;\n", localVars[j]);
            }

            // Track if the function has a return statement
            int hasReturn = 0;

            // Handle statements within the function body
            for (int j = funcBodyStart; j < funcBodyEnd; j++) {
                Statement* current = &statements[j];
                if (strcmp(current->type, "assignment") == 0) {
                    // Handle assignment
                    char tempAssign[MAX_LINE_LENGTH];
                    strcpy(tempAssign, current->content);
                    char* var = strtok(tempAssign, "<-");
                    char* expr = strtok(NULL, "<-");
                    if (var && expr) {
                        trim(var);
                        trim(expr);
                        fprintf(file, "    %s = %s;\n", var, expr);
                    }
                } else if (strcmp(current->type, "return") == 0) {
                    // Handle return
                    char tempReturn[MAX_LINE_LENGTH];
                    strcpy(tempReturn, current->content);
                    char* returnPtr = strstr(tempReturn, "return");
                    if (returnPtr != NULL) {
                        returnPtr += strlen("return");
                        trim(returnPtr);
                        fprintf(file, "    return %s;\n", returnPtr);
                        hasReturn = 1;
                    }
                } else if (strcmp(current->type, "call") == 0) {
                    // Handle function call
                    fprintf(file, "    %s;\n", current->content);
                } else if (strcmp(current->type, "print") == 0) {
                    // Handle print statement
                    char tempPrint[MAX_LINE_LENGTH];
                    strcpy(tempPrint, current->content);
                    char* exprPtr = strstr(tempPrint, "print");
                    if (exprPtr != NULL) {
                        exprPtr += strlen("print");
                        trim(exprPtr);
                        fprintf(file, "    double result = %s;\n", exprPtr);
                        fprintf(file, "    if (result == (int)result) {\n");
                        fprintf(file, "        printf(\"%%d\\n\", (int)result);\n");
                        fprintf(file, "    } else {\n");
                        fprintf(file, "        printf(\"%%.6f\\n\", result);\n");
                        fprintf(file, "    }\n");
                    }
                }
            }

            // If no return statement, add a default return
            if (!hasReturn) {
                fprintf(file, "    return 0.0;\n");
            }

            fprintf(file, "}\n\n");
            i = funcBodyEnd - 1; // Adjust outer loop index
        }
    }

    // Part 3: main Function
    fprintf(file, "int main(int argc, char* argv[]) {\n");

    // Initialize global variables (only assignments outside functions)
    for (int i = 0; i < numStatements; i++) {
        if (strcmp(statements[i].type, "function") == 0) {
            continue;
        }

        if (strcmp(statements[i].type, "assignment") == 0 && statements[i].is_indented == 0) {
            // Handle global assignment statements
            char temp[MAX_LINE_LENGTH];
            strcpy(temp, statements[i].content);
            char* var = strtok(temp, "<-");
            char* expr = strtok(NULL, "<-");
            if (var && expr) {
                trim(var);
                trim(expr);
                fprintf(file, "    %s = %s;\n", var, expr);
            }
        }
    }

    fprintf(file, "\n");

    // Handle other global statements (print and call)
    for (int i = 0; i < numStatements; i++) {
        if (strcmp(statements[i].type, "function") == 0 ||
            strcmp(statements[i].type, "assignment") == 0) {
            continue; // Already handled
        } else if (strcmp(statements[i].type, "print") == 0 && statements[i].is_indented == 0) {
            // Handle global print statement
            char expression[MAX_LINE_LENGTH];
            strcpy(expression, statements[i].content);
            char* exprPtr = strstr(expression, "print");
            if (exprPtr == NULL) continue; // Safety check
            exprPtr += strlen("print");
            trim(exprPtr);

            // Print expression result
            fprintf(file, "    double result = %s;\n", exprPtr);
            fprintf(file, "    if (result == (int)result) {\n");
            fprintf(file, "        printf(\"%%d\\n\", (int)result);\n");
            fprintf(file, "    } else {\n");
            fprintf(file, "        printf(\"%%.6f\\n\", result);\n");
            fprintf(file, "    }\n");
        } else if (strcmp(statements[i].type, "call") == 0 && statements[i].is_indented == 0) {
            // Handle global function call
            fprintf(file, "    %s;\n", statements[i].content);
        }
    }
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");
    fclose(file);

    return 0;
}

/**
 * Compiles the generated C code.
 * @param filename The name of the C file to compile.
 * @return 0 on success, -1 on error.
 */
int compileCCode(char* filename) {
    char command[1024];
    snprintf(command, sizeof(command), "cc %s -o %s.out", filename, filename);
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Compilation failed with status %d.\n", ret);
        return -1;
    }
    return 0;
}

/**
 * Executes the compiled C program.
 * @param filename The base name of the compiled executable.
 * @param argc The number of arguments.
 * @param argv The array of argument strings.
 */
void executeCProgram(char* filename, int argc, char* argv[]) {
    char executable[1024];
    snprintf(executable, sizeof(executable), "./%s.out", filename);

    // Prepare the arguments for execvp
    char** execArgs = malloc(sizeof(char*) * (argc + 2));
    if (!execArgs) {
        perror("Memory allocation failed");
        return;
    }

    execArgs[0] = executable;
    for (int i = 0; i < argc; i++) {
        execArgs[i + 1] = argv[i];
    }
    execArgs[argc + 1] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execvp(execArgs[0], execArgs);
        perror("Execution failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("Fork failed");
    }

    free(execArgs);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename.ml> [args...]\n", argv[0]);
        return 1;
    }

    char* mlFilename = argv[1];
    char cFilename[32];
    snprintf(cFilename, sizeof(cFilename), "ml-%d.c", getpid());

    Statement* statements;
    int numStatements = parseml(mlFilename, &statements);
    if (numStatements < 0) {
        fprintf(stderr, "Fail to parse ml file\n");
        return 1;
    }

    if (generateCCode(statements, numStatements, cFilename) != 0) {
        free(statements);
        return 1;
    }

    if (compileCCode(cFilename) != 0) {
        free(statements);
        return 1;
    }

    // Check if compilation was successful before execution
    char outFilename[36];
    snprintf(outFilename, sizeof(outFilename), "%s.out", cFilename);
    if (access(outFilename, F_OK) != -1) {
        executeCProgram(cFilename, argc - 2, argv + 2);
    } else {
        fprintf(stderr, "Compilation failed, cannot execute.\n");
    }

    // Delete temporary files
    remove(cFilename);
    remove(outFilename);
    free(statements);

    return 0;
}
