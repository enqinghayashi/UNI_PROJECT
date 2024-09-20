
# Project Description
We're all very familiar with higher-level programming languages, such as Python, Java, and C. They have many well-defined features, and are supported by standard libraries and modules. We'll term these large-languages.
At the other end of the scale are mini-languages, that are often embedded in other programs that don't require the support of a full programming language, or are invoked from the command-line or in a shellscript. You could consider the use of macros in MS-Excel, or the Unix command-line program bc (see man bc), as examples of a mini-languages. Chapter 8 of The Art of Unix Programming provides an overview of some (older) mini-languages [not required reading].

This project requires you write a C11 program to compile and execute a program written in a mini-language that we'll name ml. Note that there already exists a very successful programming language named ML (for Meta Language), but our mini-language is unrelated to ML (or to Machine Learning).

Writing a compiler for any programming language is an enormous task, clearly not one suited for this project. However, what many have recognised, is that C is an excellent language to support other languages, and that C has an extensive toolchain supporting compilation and linking. The strategy is to first translate programs written in other languages, such as our ml, to C, to compile that translated C code using a standard C compiler, and to finally execute the resultant program. This sequence is often termed transpiling, the 'joining' of the words translating and compiling. In this role, C is often described as a high-level assembly language, sometimes a 'wallpaper language'.

The goal of this project is to implement a C11 program, named runml, which accepts a single command-line argument providing the pathname of a text file containing a program written in ml, [added 28/8] and any optional command-line arguments to be passed the transpiled program when it is executed . Successful execution of runml will involve checking the syntax of the ml program, translating that valid ml program to a C11 program, compilation of the resultant C program and, finally, execution of the compiled program. 


# Our ml language
programs are written in text files whose names end in .ml
statements are written one-per-line (with no terminating semi-colon)
the character '#' appearing anywhere on a line introduces a comment which extends until the end of that line
only a single datatype is supported - real numbers, such as 2.71828
identifiers (variable and function names) consist of 1..12 lowercase alphabetic characters, such as budgie
there will be at most 50 unique identifiers appearing in any program
variables do not need to be defined before being used in an expression, and are automatically initialised to the (real) value 0.0
the variables arg0, arg1, and so on, provide access to the program's command-line arguments which provide real-valued numbers
a function must have been defined before it is called in an expression
each statement in a function's body (one-per-line) is indented with a tab character
functions may have zero-or-more formal parameters
a function's parameters and any other identifiers used in a function body are local to that function, and become unavailable when the function's execution completes
programs execute their statements from top-to-bottom and function calls are the only form of control-flow (yes, the language would be more useful with loops and conditions, but this project is not about designing programming languages - future work for those interested)

# The steps to compile and execute an ml program
Edit a text file named, for example, program.ml
Pass program.ml as a command-line argument to your runml program
runml validates the ml program, reporting any errors
runml generates C11 code in a file named, for example, ml-12345.c (where 12345 could be a process-ID)
runml uses your system's C11 compiler to compile ml-12345.c
runml executes the compiled C11 program ml-12345, passing any optional command-line arguments (real numbers)
runml removes any files that it created

# The ml syntax
  |       means a choice
  [...]   means zero or one
  (...)*  means zero or more

Program lines commence at the left-hand margin (no indentation).
Statements forming the body of a function are indented with a single tab.
sample01.ml, sample02.ml, sample03.ml, sample04.ml, sample05.ml, sample06.ml, sample07.ml, sample08.ml
program:
           ( program-item )*

program-item:
           statement
        |  function identifier ( identifier )*
           ←–tab–→ statement1
           ←–tab–→ statement2
           ....

statement:
           identifier "<-" expression
        |  print  expression
        |  return expression
        |  functioncall

expression:
          term   [ ("+" | "-")  expression ]

term:
          factor [ ("*" | "/")  term ]

factor:
          realconstant
        | identifier
        | functioncall
        | "(" expression ")"

functioncall:
          identifier "(" [ expression ( "," expression )* ] ")"