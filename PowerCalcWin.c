#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_EXPR_LENGTH 256

// Function prototypes
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double power(double a, double b);
double squareRoot(double a);
double logarithm(double a);
double sinFunc(double a);
double cosFunc(double a);
double tanFunc(double a);
double log10Func(double a);

int main() {
    char expression[MAX_EXPR_LENGTH];
    double result;

    printf("Advanced Calculator\n");
    printf("Operations supported: +, -, *, /, ^, sqrt, log, sin, cos, tan, log10\n");
    printf("Enter an expression (or 'exit' to quit): ");
    
    while (1) {
        fgets(expression, MAX_EXPR_LENGTH, stdin);

        // Exit condition
        if (strncmp(expression, "exit", 4) == 0) {
            printf("Exiting the calculator.\n");
            break;
        }

        // Use sscanf or other methods for more complex input parsing
        // Here we handle basic operations with simple format
        double num1, num2;
        char operator;

        // Check for simple operations
        if (sscanf(expression, "%lf %c %lf", &num1, &operator, &num2) == 3) {
            switch (operator) {
                case '+':
                    result = add(num1, num2);
                    break;
                case '-':
                    result = subtract(num1, num2);
                    break;
                case '*':
                    result = multiply(num1, num2);
                    break;
                case '/':
                    if (num2 == 0) {
                        printf("Error: Division by zero!\n");
                        continue;
                    }
                    result = divide(num1, num2);
                    break;
                case '^':
                    result = power(num1, num2);
                    break;
                default:
                    printf("Invalid operator.\n");
                    continue;
            }
        } else if (sscanf(expression, "sqrt %lf", &num1) == 1) {
            if (num1 < 0) {
                printf("Error: Square root of negative number!\n");
                continue;
            }
            result = squareRoot(num1);
        } else if (sscanf(expression, "log %lf", &num1) == 1) {
            if (num1 <= 0) {
                printf("Error: Logarithm of non-positive number!\n");
                continue;
            }
            result = logarithm(num1);
        } else if (sscanf(expression, "log10 %lf", &num1) == 1) {
            if (num1 <= 0) {
                printf("Error: Logarithm base 10 of non-positive number!\n");
                continue;
            }
            result = log10Func(num1);
        } else if (sscanf(expression, "sin %lf", &num1) == 1) {
            result = sinFunc(num1);
        } else if (sscanf(expression, "cos %lf", &num1) == 1) {
            result = cosFunc(num1);
        } else if (sscanf(expression, "tan %lf", &num1) == 1) {
            result = tanFunc(num1);
        } else {
            printf("Invalid input format.\n");
            continue;
        }

        printf("Result: %.6f\n", result);
        printf("Enter an expression (or 'exit' to quit): ");
    }

    return 0;
}

// Function implementations
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return a / b;
}

double power(double a, double b) {
    return pow(a, b);
}

double squareRoot(double a) {
    return sqrt(a);
}

double logarithm(double a) {
    return log(a);
}

double sinFunc(double a) {
    return sin(a);
}

double cosFunc(double a) {
    return cos(a);
}

double tanFunc(double a) {
    return tan(a);
}

double log10Func(double a) {
    return log10(a);
}
