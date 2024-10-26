# LAB - 1

This file covers the various **Linux commands**, **pipes**, **redirection**, and **regex concepts** discussed step-by-step throughout the chat, along with detailed **examples** and explanations.

---

## 1. **Shell Basics and Commands**

### **Command: `echo`**
- **Usage:** Display text or variables on the terminal.
- **Syntax:** 
  ```bash
  echo "Hello, World!"
  ```
- **Output:**
  ```
  Hello, World!
  ```

---

## 2. **Clearing the Terminal**

### **Command: `clear`**
- **Usage:** Clears the screen and positions the prompt and cursor at the top-left corner.
- **Syntax:** 
  ```bash
  clear
  ```

---

## 3. **Displaying Manual Pages**

### **Command: `man`**
- **Usage:** Opens the manual page for a command.
- **Syntax:** 
  ```bash
  man <command_name>
  ```
- **Example:** Display the manual for the `date` command.
  ```bash
  man date
  ```

---

## 4. **Counting Lines, Words, and Characters**

### **Command: `wc`**
- **Usage:** Displays counts of lines, words, or bytes.
- **Syntax:** 
  ```bash
  wc [options] <file_name>
  ```
- **Options:**
  - `-l`: Count lines.
  - `-w`: Count words.
  - `-c`: Count bytes.
- **Example:**
  ```bash
  wc -l /path/to/file.txt
  ```

---

## 5. **Using Pipes**

### **Piping Commands Together**
- **Usage:** Connect the output of one command to another.
- **Syntax:**
  ```bash
  command1 | command2
  ```
- **Example:** Count the number of files in the current directory.
  ```bash
  ls | wc -l
  ```

---

## 6. **Creating Files and Directories**

### **Command: `mkdir`**
- **Usage:** Creates directories.
- **Syntax:**
  ```bash
  mkdir <directory_name>
  ```
- **Example:**
  ```bash
  mkdir my_folder
  ```

### **Command: `touch`**
- **Usage:** Creates an empty file or updates the timestamp of a file.
- **Syntax:**
  ```bash
  touch <file_name>
  ```
- **Example:**
  ```bash
  touch file1.txt
  ```

---

## 7. **Searching in Files using `grep`**

### **Command: `grep`**
- **Usage:** Searches for patterns in files.
- **Syntax:**
  ```bash
  grep <pattern> <file_name>
  ```
- **Example:**
  ```bash
  grep "hello" myfile.txt
  ```

### **Search for Multiple Patterns with `-E`:**
- **Syntax:**
  ```bash
  grep -E 'pattern1|pattern2' <file_name>
  ```
- **Example:**
  ```bash
  grep -E 'hello|world' myfile.txt
  ```

---

## 8. **Sorting Files**

### **Command: `sort`**
- **Usage:** Sorts the contents of a file.
- **Syntax:**
  ```bash
  sort <file_name>
  ```
- **Example:** Sort in **reverse order**:
  ```bash
  sort -r myfile.txt
  ```

---

## 9. **Using Regex in Linux**

### **Basic Regex Concepts**
- `[ ]`: Character class to match any one character inside the brackets.
- `[^ ]`: Negated class, matches any character **not inside** the brackets.
- `.`: Matches any single character (except newline).
- `*`: Matches **zero or more occurrences** of the previous character.
- `^`: Anchors the match to the **start of the line**.
- `$`: Anchors the match to the **end of the line**.

### **Examples**:

1. **Files Starting with `c` or `h`:**
   ```bash
   ls | grep "^[ch]"
   ```

2. **Files Ending with `.txt`:**
   ```bash
   ls | grep "\.txt$"
   ```

3. **Files with Base Name Ending in `1`:**
   ```bash
   ls | grep "1\..*$"
   ```

4. **Files Containing `a` in the Base Name:**
   ```bash
   ls | grep -E "^[^.]*a[^.]*\."
   ```

---

## 10. **Using `find` for Advanced Search**

### **Command: `find`**
- **Usage:** Searches for files in directories recursively.
- **Syntax:**
  ```bash
  find <directory> -type f -name <pattern>
  ```
- **Example:**
  ```bash
  find . -type f -name "*1.*"
  ```

---

## Conclusion
This guide provides a detailed look at essential **Linux commands**, **pipes**, **redirection**, and **regex patterns**. Each command is accompanied by examples to illustrate practical usage. With these tools, you can efficiently navigate, search, and manipulate files and directories on a Linux/macOS system.


# LAB - 2 

## Introduction to Shell Scripts
A **shell script** is a sequence of Linux commands saved in a file that can be executed like a program. 
Before executing a script, it is essential to **give it permission** to run using:

```bash
chmod +x scriptname
```

To execute a shell script, use:
```bash
./scriptname [arguments]
```

---

## Script to Display First Argument and File Line Count
This script prints the script name, a string using the first argument, and counts the number of lines in a given file.

### **Script (`script.sh`):**
```bash
cat > script.sh
echo "First argument is $0"
echo "World loves $1"
echo "The number of lines in file $3 are `cat $3 | wc -l`"
```

### **Usage:**
```bash
./script.sh User pasta.txt
```
### **Explanation:**
- **`$0`**: Displays the script name.
- **`$1`**: Displays the first argument passed (`User` in this case).
- **`$3`**: Refers to the third argument (in this case, `pasta.txt`) and counts its lines.

---

## Using Shell Patterns and Argument Expansion
The command-line shell can **expand patterns** before passing them to a script. When running:
```bash
./script.sh /path/to/directory *.[a-z]
```
This expands `*.[a-z]` to **all files** matching the pattern. However, only the **first file** (e.g., `a.c`) becomes `$2`.

### Solution: Using Shift
To correctly handle all matching files:
```bash
#!/bin/bash
cd $1
shift
ls "$@"
```

---

## Counting Number of Files with a Specific Pattern
This script changes into the specified directory and **lists all files matching** `*.[a-z]`.

### **Script:**
```bash
#!/bin/bash
cd $1
ls *.[a-z]
```

### **Usage:**
```bash
./script.sh /path/to/directory
```

If files like `a.c` and `a1.c` exist, they will be displayed.

---

## Counting Regular Files using `ls` and `grep`
The following script counts **only regular files** in a directory:

### **Script:**
```bash
#!/bin/bash
cd $1
ls -l | grep "^-" | wc -l
```

### **Explanation:**
- **`ls -l`**: Lists all files and directories in long format.
- **`grep "^-"`**: Filters only regular files (lines starting with `-`).
- **`wc -l`**: Counts the number of lines (i.e., the number of regular files).

---

## Combining Files and Sorting Unique Values
### **Steps:**
1. Create two files:
   ```bash
   cat > a1.sh
   1
   1
   ^C
   cat > a2.sh
   1
   2
   ^C
   ```

2. Combine the files:
   ```bash
   cat a1.sh > a3.sh
   cat a2.sh >> a3.sh
   ```

3. View the contents of `a3.sh`:
   ```bash
   cat a3.sh
   ```
   Output:
   ```
   1
   1
   1
   2
   ```

4. Sort and remove duplicates:
   ```bash
   sort a3.sh -u
   ```
   Output:
   ```
   1
   2
   ```

### **Explanation:**
- **`cat`**: Concatenates and copies the content of files.
- **`>`**: Overwrites content.
- **`>>`**: Appends content.
- **`sort -u`**: Sorts the content and removes duplicates.

---

## Conclusion
This document covered various shell scripting concepts, including how to:
1. Write and execute basic shell scripts.
2. Handle shell patterns and argument expansion.
3. Count files and use redirection operators.
4. Combine and sort file content.

Feel free to explore and modify these examples to deepen your understanding of shell scripting!


# LAB - 3

This document provides detailed explanations of shell scripting techniques covered between pages 32-37 in the *CSE 3142 OSLAB* manual, along with resolved doubts on various questions and examples. It outlines comments, variables, conditionals, loops, arithmetic operations, and more essential shell scripting concepts. 

---

## 1. Comments  
- **Syntax**: 
  ```shell
  # This is a comment
  ```
  Everything after the `#` symbol on a line is treated as a comment and ignored by the shell.

---

## 2. Variables  
- **Declaring Variables**:
  ```shell
  declare -a teamnames
  teamnames[0]="India"
  teamnames[1]="England"
  echo "There are ${#teamnames[*]} teams"
  unset teamnames[1]
  ```
  In the example above:
  - `declare -a` creates an array.
  - `${#teamnames[*]}` accesses the total elements in the array.
  - `unset` deletes a specific array element.

---

## 3. Aliases  
- **Creating and Using Aliases**:
  ```shell
  alias dir="ls -aF"
  dir
  ```
  Aliases allow defining custom commands or shortcuts to frequently used commands.

---

## 4. Arithmetic Operations  
- **Using `expr` for arithmetic calculations**:
  ```shell
  x=1
  x=`expr $x + 1`
  echo $x
  ```
  **Explanation**: `expr` evaluates arithmetic expressions. In the example, we increment the value of `x` by 1.

---

## 5. Test Expressions  
- **Using `test` to perform evaluations**:
  ```shell
  if test $x -eq 10; then
    echo "x is equal to 10"
  fi
  ```
  **Explanation**: 
  - `-eq`: Checks equality.
  - `-gt`: Checks if greater than.
  - `-r <file>`: Checks if the file is readable.
  - `-f <file>`: Checks if it is a regular file.

---

## 6. Conditional Statements  
- **If-else statement**:
  ```shell
  echo "Enter a number:"
  read number
  if [ $number -lt 0 ]; then
    echo "Negative"
  elif [ $number -eq 0 ]; then
    echo "Zero"
  else
    echo "Positive"
  fi
  ```
  **Explanation**: This structure executes different commands based on conditions.

- **Case statement**:
  ```shell
  case $1 in
    *.c) 
      cc $1 ;;  # Compile .c files
    *.sh) 
      echo "Shell script";;
    *)
      echo "Unknown file type";;
  esac
  ```
  **Explanation**: The `case` structure matches patterns and executes corresponding commands.

---

## 7. Loop Structures  
### 7.1 While Loop
```shell
X=0
while [ $X -le 5 ]; do
  echo $X
  X=$((X+1))
done
```
**Explanation**: Executes the loop as long as the condition is true.

### 7.2 Until Loop
```shell
x=5
until [ $x -le 0 ]; do
  echo $x
  x=$((x-1))
done
```
**Explanation**: This loop runs until the condition becomes true.

### 7.3 For Loop
```shell
for item in 1 2 3 4 5; do
  echo "Item: $item"
done
```
**Explanation**: Iterates through a list of items and executes commands for each.

---

## Example Summary  
The examples provided demonstrate key shell scripting concepts such as conditionals, loops, and arithmetic operations. These fundamental syntaxes allow for automating tasks in Linux, facilitating system administration and process management. Understanding these will enable you to create powerful and flexible shell scripts for various operations.


# Lab - 4

## 1. `write()` System Call
The `write` system call writes data to a file descriptor. It takes three parameters:
```c
#include <unistd.h>
size_t write(int fildes, const void *buf, size_t nbytes);
```
- **`fildes`**: File descriptor.
- **`buf`**: Buffer containing the data to write.
- **`nbytes`**: Number of bytes to write.

### Example:
```c
#include <unistd.h>
#include <stdlib.h>

int main() {
    if (write(1, "Hello, world!\n", 13) != 13) {
        write(2, "A write error occurred.\n", 24);
    }
    exit(0);
}
```

---

## 2. `read()` System Call
Reads data from a file descriptor into a buffer.
```c
#include <unistd.h>
size_t read(int fildes, void *buf, size_t nbytes);
```
- **`fildes`**: File descriptor to read from.
- **`buf`**: Buffer to store the read data.
- **`nbytes`**: Maximum number of bytes to read.

---

## 3. `open()` System Call
Used to open a file and return a file descriptor.
```c
#include <fcntl.h>
int open(const char *path, int oflags, mode_t mode);
```
- **`path`**: Path to the file.
- **`oflags`**: Flags for opening the file (e.g., `O_RDONLY` for read-only).
- **`mode`**: Permissions if the file is created.

### Example:
```c
int fd = open("example.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
```

---

## 4. `close()` System Call
Closes an open file descriptor.
```c
#include <unistd.h>
int close(int fildes);
```
- **`fildes`**: File descriptor to close.

---

## 5. `lseek()` System Call
Moves the read/write file offset.
```c
#include <unistd.h>
off_t lseek(int fildes, off_t offset, int whence);
```
- **`fildes`**: File descriptor.
- **`offset`**: Byte offset to move.
- **`whence`**: Starting point for offset (`SEEK_SET`, `SEEK_CUR`, `SEEK_END`).

---

## 6. `fork()` System Call
Creates a new process.
```c
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
```
- **Returns**: 
  - `0` to the child process.
  - Child's PID to the parent process.

### Example:
```c
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("This is the child process.\n");
    } else {
        printf("This is the parent process.\n");
    }
    return 0;
}
```

---

## 7. `getpid()` and `getppid()` System Calls
Retrieve process identifiers.
```c
#include <sys/types.h>
#include <unistd.h>

pid_t getpid(void);   // Returns the current process ID.
pid_t getppid(void);  // Returns the parent process ID.
```

---

## Error Handling with `errno`
When system calls fail, they return `-1` and set the `errno` variable with the appropriate error code. To use `errno`, include:
```c
#include <errno.h>
```

---

## Conclusion
These system calls form the foundation of Linux programming. Mastering them will enable you to perform various tasks, from file management to process control.
