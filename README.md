<div align="center">
<h1 align="center">
    <br>In process...</br>
    <br>Minishell</br>
</h1>
<p align="center">
    <img src="https://img.shields.io/badge/Barcelona-100000?style=flat-square&logo=42&logoColor=white&labelColor=000000&color=000000" alt="42 Barcelona"/>
</p>
</div>

## Table of Contents
- [Summary](#-summary)
- [Project breakdown](#-projectbreakdown)
- [Mandatory functionalities](#-mandatoryfuncionalities)
- [Usage](#-usage)
- [Screenshots](#-screenshots)
- [Installation](#-installation)


# Summary

### What is "Minishell"?

It's a long project in a group of two, the goal is to create a command interpreter that mimics the behavior of bash. Minishell manages environment variables,
launches programs and handles their return. We also have a number of built-in functions, like cd, echo, env, exit, export, pwd and unset. In any moment of doubt, our teacher, professor, mentor, was simply bash. So, in our research phase, we turned to the bash manual, https://www.gnu.org/software/bash/manual/bash.html 

From there we learned that bash is mainly composed of 4 phases, tokenisation, parsing or creation of the command table, expansion and execution. Big blocks that will be broken down into smaller ones.

# Mandatory functionalities

- Display a promt while waiting for a new commmand.
- Have a clean working history.
- Find and launch executables (using the PATH variable or an absolute path).
- Handle ' (single) and " (double) quotes like in bash.
- Implement redirections such as:
-     < redirect input.
      > redirect output.
      << heredoc.
      >> redirect output in append mode.
- Implement pipes.
- Handle environment and export variables.
- Handle $?.
- Signals ctrl-C, ctrl-D, and ctrl-\ should behave like in bash.
- Recreate the following builtins:
-     echo with -n flag.
      cd with only a relative or absolute path.
      pwd (without flags)
      export (without flags)
      unset (without flags)
      env (without flags or arguments)
      exit (without flags)

# Project Breakdown

### Extraction of the information.

We receive our input line from the readline, and first we pass it to a function that checks that the inverted commas are properly closed, each one with its specific pair, it is a first phase of previous checking. Then we enter the tokenisation. 
In this phase we will give a value to each argument that we read, depending on whether it is an operator ("<", ">", "<<", ">>" or "|") or an argument. We do all this by creating a linked list of nodes, in which we associate a value to a string. We send it to the second big block, the parse or command table creation.

### Parsing

This phase consists of processing each simple command separately, with the pipe "|" as separator, we can act as follows.

First we start by parsing the redirects, inside the new simple command node, we add a linked list for the redirects, one or all of them, each node will contain the operator and the following str, which we deduce is the argument of the operator, either the input file, the output file or the EOF in the case of heredoc. 
Each node that we read and process from the tokenisation list is eliminated, so we do a process of separation by elimination, if we first remove the redirections what we are left with is the command with its flags or arguments. 
We also take the opportunity to analyse if the command introduced is a builtin or not, this will help us later to know if we have to execute our own builtin and to know whether to proceed to create a child process or not, since for the builtin we do not have to do it.

### Built-ins

- cd = Changes the directory to the specified one, updating the environment variables of pwd and oldpwd. We have added the following flags:
-     cd with no arguments goes to the /home directory.
      cd ~ goes to the /home directory
      cd - goes to the old directory.
- echo = displays a line of text. The "-n" flag has been added which prints without the line break.
- pwd = displays the current directory.
- env = display environment variables.
- export = adds or modifies an environment variable. If "export hello=world" is run, it creates a new one.
-     If export hello=world hello+="hello    " returns hello=hello=hello    world is executed,
      it checks if it exists, and if so, modifies it, you can use quotes or without quotes for
      the value of the variable. If executed without arguments, it displays the exported variables.
- unset = can be executed with one or more arguments. It checks if the variable exists, and if so, proceeds to delete it.


## Screenshots

![App Screenshot](./screenshot.png)

## Installation

1. Clone the minishell repository:
```sh
git clone
```

2. Change to the project directory:
```sh
cd minishell
```

3. Compile the library:

    Using Makefile you can create the executable file "minishell":
    ```sh
    make
    ```
    to run minishell
    ```sh
    ./minishell
    ```
    * For mac: before run
    ```sh
    brew install readline
    ```
** Works on linux as well as on Mac.


[**Return**](#Top)
