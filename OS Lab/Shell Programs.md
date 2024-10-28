
# Shell Script Programs Collection 🐚

This document contains a collection of useful shell scripts that perform a variety of tasks. Each program is explained with headings and examples to help you understand their functionality.

---

## 1. Armstrong Number Checker

**Description:**  
This program checks whether the given number is an Armstrong number (e.g., 153 = 1³ + 5³ + 3³).

**Code:**
```bash
#!/bin/bash
echo "Enter a number"
read num
cpy=$num
arm=0

while (( cpy != 0 )); do
    rem=$(( cpy % 10 ))
    arm=$(( arm + rem * rem * rem ))
    cpy=$(( cpy / 10 ))
done

if (( arm == num )); then
    echo "It is an Armstrong number"
else
    echo "Not an Armstrong number"
fi
```

---

## 2. Simple Calculator

**Description:**  
This script performs basic arithmetic operations (addition, subtraction, multiplication, and division).

**Code:**
```bash
#!/bin/bash
echo "Enter first number"
read a
echo "Enter second number"
read b
echo "Enter operation (+, -, *, /)"
read c
ans=0

case $c in
    "+")
        ans=$((a+b))
        echo "Answer is $ans"
        ;;
    "-")
        ans=$((a-b))
        echo "Answer is $ans"
        ;;
    "*")
        ans=$((a*b))
        echo "Answer is $ans"
        ;;
    "/")
        if (( b==0 || b>a )); then
            echo "Not allowed"
        else
            ans=$((a/b))
            echo "Answer is $ans"
        fi
        ;;
    *)
        echo "Invalid"
        ;;
esac
```

---

## 3. Even or Odd Checker

**Description:**  
This program checks whether a given number is even or odd.

**Code:**
```bash
#!/bin/bash
echo "Enter a number"
read num

if (( num % 2 == 0 )); then
    echo "$num is even"
else
    echo "$num is odd"
fi
```

---

## 4. Factorial Calculator

**Description:**  
This script calculates the factorial of a given number.

**Code:**
```bash
#!/bin/bash
echo "Enter a number"
read num
fact=1

for (( i = 1; i <= num; i++ )); do
    fact=$(( fact * i ))
done

echo "Factorial of $num is $fact"
```

---

## 5. Palindrome Checker

**Description:**  
This program checks whether a given string is a palindrome (the same forwards and backwards).

**Code:**
```bash
#!/bin/bash
echo "Enter a string"
read str

reverse=$(echo "$str" | rev)

if [ "$str" == "$reverse" ]; then
    echo "$str is a palindrome"
else
    echo "$str is not a palindrome"
fi
```

---

## 6. Prime Number Checker

**Description:**  
This script checks whether the given number is a prime number.

**Code:**
```bash
#!/bin/bash
echo "Enter a number"
read num
is_prime=1

for (( i = 2; i * i <= num; i++ )); do
    if (( num % i == 0 )); then
        is_prime=0
        break
    fi
done

if (( is_prime && num > 1 )); then
    echo "$num is a prime number"
else
    echo "$num is not a prime number"
fi
```

---

## 7. Sum of Numbers in a Range

**Description:**  
This program calculates the sum of all numbers between a given range.

**Code:**
```bash
#!/bin/bash
echo "Enter the start of the range"
read start
echo "Enter the end of the range"
read end
sum=0

for (( i = start; i <= end; i++ )); do
    sum=$(( sum + i ))
done

echo "The sum of numbers from $start to $end is $sum"
```

---

## 8. Fibonacci Series Generator

**Description:**  
This script generates the Fibonacci series up to a given number of terms.

**Code:**
```bash
#!/bin/bash
echo "Enter the number of terms"
read n
a=0
b=1

for (( i = 0; i < n; i++ )); do
    echo -n "$a "
    next=$(( a + b ))
    a=$b
    b=$next
done
echo ""
```

---

## 9. Vowel and Consonant Counter

**Description:**  
This program counts the number of vowels and consonants in a given string.

**Code:**
```bash
#!/bin/bash
echo "Enter a string"
read str
vowels=0
consonants=0

for (( i = 0; i < ${#str}; i++ )); do
    char=${str:i:1}
    if [[ "$char" =~ [AEIOUaeiou] ]]; then
        ((vowels++))
    elif [[ "$char" =~ [a-zA-Z] ]]; then
        ((consonants++))
    fi
done

echo "Vowels: $vowels, Consonants: $consonants"
```

---

## 10. Countdown Timer

**Description:**  
This script counts down from a given number of seconds.

**Code:**
```bash
#!/bin/bash
echo "Enter the number of seconds"
read seconds

while (( seconds > 0 )); do
    echo "$seconds..."
    sleep 1
    ((seconds--))
done

echo "Time's up!"
```
