
# Basic Shell Scripting Rules

## 1. Start with the Shebang (#!)
- Always specify the interpreter to use (e.g., `bash` or `sh`).
```bash
#!/bin/bash
```

## 2. Make the Script Executable
```bash
chmod +x script_name.sh
```

## 3. Comments for Documentation
- Use `#` for comments.
```bash
# This is a comment
echo "Hello, World!"
```

## 4. Variables and Naming Rules
- No spaces around `=` when assigning values.
- Access variables with `$`.
```bash
name="Alice"
age=25
echo "My name is $name and I am $age years old."
```

## 5. Use Quotes to Handle Spaces
```bash
greeting="Hello, World!"
echo "$greeting"
```

## 6. Command Substitution
- Use backticks or `$(...)`.
```bash
current_date=$(date)
echo "Today is $current_date"
```

## 7. Conditional Statements (if-else)
```bash
if (( number % 2 == 0 )); then
    echo "Even"
else
    echo "Odd"
fi
```

## 8. Loops (for, while)
### For Loop:
```bash
for i in {1..5}; do
    echo "Number: $i"
done
```
### While Loop:
```bash
count=1
while [ $count -le 5 ]; do
    echo "Count: $count"
    ((count++))
done
```

## 9. Use Exit Status ($?) to Check for Errors
```bash
mkdir test_directory
if [ $? -eq 0 ]; then
    echo "Directory created successfully!"
else
    echo "Failed to create directory."
fi
```

## 10. Handle Command-Line Arguments
```bash
echo "First argument: $1"
echo "Second argument: $2"
```

## 11. Use Functions for Reusability
```bash
greet() {
    echo "Hello, $1!"
}
greet "Alice"
```

## 12. Redirect Input and Output
```bash
echo "Hello, World!" > output.txt
echo "This is a new line." >> output.txt
```

## 13. Use trap to Handle Signals Gracefully
```bash
trap "echo 'Script interrupted!'; exit" SIGINT
while true; do
    echo "Running..."
    sleep 1
done
```

## 14. Use set to Debug and Improve Script Safety
```bash
set -e  # Exit on error
set -u  # Treat unset variables as an error
set -o pipefail  # Catch errors in pipelines
```

## 15. Use read to Get User Input
```bash
echo "Enter your name:"
read name
echo "Hello, $name!"
```

## Summary of Key Rules
1. Start with `#!/bin/bash`.
2. Make the script executable with `chmod +x`.
3. Use comments for clarity.
4. Avoid spaces around `=` in variable assignments.
5. Handle spaces with quotes.
6. Use `if-else` and loops for logic.
7. Manage command-line arguments with `$1`, `$2`, etc.
8. Check exit status with `$?`.
9. Use functions to make code modular.
