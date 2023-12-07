# Algorithms and Data Structures 
This repository contains the implementation of some algorithms and data structures in C++, I have done for my Algorithms and Data Structures 2023/24 course at the Warsaw University of Technology. It is meant as a future reference for me and a learning resource for others. The code is not meant to be used in production. It is not optimized and it does not handle all possible edge cases. The code is meant to be used for learning purposes only. 

`WARNING: The code is not commented and this README is not complete as of yet and partly auto-generated. For more accurate information about programs, please refer to the corresponding pdfs of the tasks, that are provided.`

## Table of Contents
- [Lab0](#lab0)
  - [Task 1 - Longest Increasing Subsequence (LIS)](#task-1---longest-increasing-subsequence-lis)
  - [Task 2 - Implementation of a ArrayStack data structure](#task-2---implementation-of-a-arraystack-data-structure)


## Lab0
### Task 1 - Longest Increasing Subsequence (LIS)
#### Description
The task is to find the longest increasing subsequence of a given sequence of numbers. The subsequence does not have to be continuous. The program should print the length of the longest increasing subsequence and the subsequence itself. If there are multiple solutions, the program should print the one that is lexicographically smallest. The program should be implemented in O(n^2) time complexity and O(n) space complexity. Full description can be found in the corresponding [pdf](Lab0/LIS%20(longest%20increasing%20subsequence)/LIS.pdf).

#### Solution
The solution is based on dynamic programming. The program uses an array of size n to store the length of the longest increasing subsequence ending at the i-th element of the sequence. The program also uses an array of size n to store the index of the previous element of the longest increasing subsequence ending at the i-th element of the sequence. The program iterates over the sequence and for each element it iterates over all previous elements to find the longest increasing subsequence ending at the i-th element. The program also keeps track of the index of the longest increasing subsequence ending at the i-th element. After the iteration, the program finds the longest increasing subsequence by iterating over the array of the length of the longest increasing subsequence ending at the i-th element of the sequence and finding the longest one. Then the program prints the length of the longest increasing subsequence and the subsequence itself by iterating over the array of the index of the previous element of the longest increasing subsequence ending at the i-th element of the sequence and printing the elements in reverse order.

#### Complexity
The time complexity of the solution is O(n^2) because the program iterates over the sequence and for each element it iterates over all previous elements. The space complexity of the solution is O(n) because the program uses two arrays of size n.

#### Usage
The program takes the sequence as an input from the standard input. The first line of the input should contain the length of the sequence. The second line of the input should contain the sequence. The program prints the length of the longest increasing subsequence and the subsequence itself.

#### Example
Input:
```bash
10
1 2 3 4 5 6 7 8 9 10
```
Output:
```bash
10
1 2 3 4 5 6 7 8 9 10
```

### Task 2 - Implementation of a ArrayStack data structure
#### Description
The task is to implement a ArrayStack data structure. The data structure should be implemented using an array. The data structure should support the following operations: push, pop, top, size, empty. Full description can be found in the corresponding [pdf](Lab0/ArrayStack/ArrayStack.pdf).

#### Solution
The solution is based on an array. The data structure uses an array to store the elements. The data structure also uses an integer to store the index of the top element of the stack. The data structure supports the following operations: push, pop, top, size, empty. The push operation inserts an element at the top of the stack. The pop operation removes the top element of the stack. The top operation returns the top element of the stack. The size operation returns the number of elements in the stack. The empty operation returns true if the stack is empty and false otherwise.

#### Complexity
The time complexity of the push, pop, top, size, empty operations is O(1) because the operations do not iterate over the elements of the stack. The space complexity of the data structure is O(n) because the data structure uses an array of size n.

#### Usage
The program takes the input from the standard input. The first line of the input should contain the number of operations. The following lines should contain the operations. The operations should be in the following format: push x, pop, top, size, empty. The program prints the results of the operations.

#### Example
Input:
```bash
10
push 1  
push 2
push 3
top
size
empty
pop
pop
pop
pop
```

Output:
```bash
3
3
0
3
2
1
0
```