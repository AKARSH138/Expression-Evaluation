# Expression Evaluation Using Stack in C

## 1. Introduction
Expression evaluation a mathematical expression from Infix notation to Postfix notation and evaluates the resulting Postfix expression using Stack operations.

## 2. Objectives
- To understand the implementation of Stack using arrays.
- To convert Infix expressions into Postfix expressions.
- To evaluate Postfix expressions using Stack.
- To understand operator precedence and associativity.

## 3. Data Structure Used
**Stack (LIFO – Last In, First Out)**

The project uses two stacks:
- Operator Stack: Stores operators during Infix to Postfix conversion.
- Evaluation Stack: Stores operands and intermediate results during Postfix evaluation.

## 4. Supported Operations
- Addition (+)
- Subtraction (-)
- Multiplication (*)
- Division (/)
- Exponentiation (^)
- Parentheses ( )

The program supports non-negative integer operands and multi-digit numbers. Division uses integer arithmetic.

## 5. Algorithm

### A. Infix to Postfix Conversion
1. Read the infix expression from the user.
2. If the character is an operand, add it to the postfix expression.
3. If it is an opening parenthesis, push it onto the stack.
4. If it is a closing parenthesis, pop operators until the opening parenthesis is found.
5. If it is an operator, compare its precedence with the operator at the top of the stack.
6. Pop operators with higher precedence (or equal precedence for left-associative operators).
7. Push the current operator onto the stack.
8. Pop all remaining operators and complete the postfix expression.

### B. Postfix Evaluation
1. Read the postfix expression from left to right.
2. If the token is an operand, push it onto the evaluation stack.
3. If the token is an operator, pop two operands.
4. Perform the corresponding arithmetic operation.
5. Push the result back onto the stack.
6. The final value remaining in the stack is the answer.

## 6. Sample Input and Output

**Input:**
```text
5+6*2
```

**Postfix Expression:**
```text
5 6 2 * +
```

**Evaluated Result:**
```text
17
```

## 7. Programming Language
C Programming Language

## 8. Conclusion
This project demonstrates how Stack data structures can be used to convert and evaluate mathematical expressions. It also provides an understanding of operator precedence, associativity, PUSH and POP operations.

## 9. Source Code
`expression_evaluation.c`
