
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define SIZE 200

// Stack for operators
char opStack[SIZE];
int top = -1;

// Stack for evaluation
int evalStack[SIZE];
int evalTop = -1;

// Function to push operator
void pushOperator(char ch)
{
    opStack[++top] = ch;
}

// Function to pop operator
char popOperator()
{
    return opStack[top--];
}

// Function to find operator precedence
int precedence(char ch)
{
    if(ch == '^')
        return 3;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '+' || ch == '-')
        return 1;

    return 0;
}

// Function to convert infix to postfix
int infixToPostfix(char infix[], char postfix[])
{
    int i = 0, j = 0;

    while(infix[i] != '\0')
    {
        // Ignore spaces
        if(isspace((unsigned char)infix[i]))
        {
            i++;
        }

        // If operand is a number
        else if(isdigit((unsigned char)infix[i]))
        {
            while(isdigit((unsigned char)infix[i]))
            {
                postfix[j++] = infix[i++];
            }

            postfix[j++] = ' ';
        }

        // If opening bracket
        else if(infix[i] == '(')
        {
            pushOperator(infix[i]);
            i++;
        }

        // If closing bracket
        else if(infix[i] == ')')
        {
            while(top != -1 && opStack[top] != '(')
            {
                postfix[j++] = popOperator();
                postfix[j++] = ' ';
            }

            if(top == -1)
                return 0;

            popOperator();
            i++;
        }

        // If operator
        else if(infix[i] == '+' || infix[i] == '-' ||
                infix[i] == '*' || infix[i] == '/' ||
                infix[i] == '^')
        {
            char current = infix[i];

            while(top != -1 && opStack[top] != '(' &&
                  (precedence(opStack[top]) > precedence(current) ||
                  (precedence(opStack[top]) == precedence(current)
                  && current != '^')))
            {
                postfix[j++] = popOperator();
                postfix[j++] = ' ';
            }

            pushOperator(current);
            i++;
        }

        else
        {
            return 0;
        }
    }

    // Pop remaining operators
    while(top != -1)
    {
        if(opStack[top] == '(')
            return 0;

        postfix[j++] = popOperator();
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';

    return 1;
}

// Function to push number into evaluation stack
void pushNumber(int num)
{
    evalStack[++evalTop] = num;
}

// Function to pop number from evaluation stack
int popNumber()
{
    return evalStack[evalTop--];
}

// Function to evaluate postfix expression
int evaluatePostfix(char postfix[], int *result)
{
    char *token = strtok(postfix, " \t\n");

    while(token != NULL)
    {
        // If token is a number
        if(isdigit((unsigned char)token[0]))
        {
            char *end;
            long num = strtol(token, &end, 10);

            if(*end != '\0' || num > 2147483647L)
                return 0;

            pushNumber((int)num);
        }

        // If token is an operator
        else if(strlen(token) == 1)
        {
            char op = token[0];

            if(op == '+' || op == '-' || op == '*' ||
               op == '/' || op == '^')
            {
                if(evalTop < 1)
                    return 0;

                int b = popNumber();
                int a = popNumber();
                int ans;

                switch(op)
                {
                    case '+':
                        ans = a + b;
                        break;

                    case '-':
                        ans = a - b;
                        break;

                    case '*':
                        ans = a * b;
                        break;

                    case '/':
                        if(b == 0)
                            return 0;

                        ans = a / b;
                        break;

                    case '^':
                        if(b < 0)
                            return 0;

                        ans = (int)pow(a, b);
                        break;

                    default:
                        return 0;
                }

                pushNumber(ans);
            }
            else
                return 0;
        }
        else
            return 0;

        token = strtok(NULL, " \t\n");
    }

    if(evalTop != 0)
        return 0;

    *result = popNumber();

    return 1;
}

// Main function
int main()
{
    char infix[SIZE];
    char postfix[SIZE];
    int result;

    printf("EXPRESSION EVALUATION USING STACK\n");

    printf("Enter an infix expression: ");
    fgets(infix, SIZE, stdin);

    if(!infixToPostfix(infix, postfix))
    {
        printf("Invalid infix expression!\n");
        return 1;
    }

    printf("\nPostfix Expression: %s\n", postfix);

    if(!evaluatePostfix(postfix, &result))
    {
        printf("Invalid postfix expression or division by zero!\n");
        return 1;
    }

    printf("Evaluated Result: %d\n", result);

    return 0;
}
