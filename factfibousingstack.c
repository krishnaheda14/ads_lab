#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int top;
    int items[MAX];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->items[++s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->items[s->top--];
}

int factorial(int n) {
    Stack s;
    initStack(&s);
    int result = 1;

    for (int i = n; i > 1; i--) {
        push(&s, i);
    }

    while (!isEmpty(&s)) {
        result *= pop(&s);
    }

    return result;
}

void generateFibonacci(int n) {
    Stack s;
    initStack(&s);

    if (n < 1) {
        printf("The number of terms must be at least 1.\n");
        return;
    }

    push(&s, 0);
    if (n > 1) {
        push(&s, 1);
    }

    for (int i = 2; i < n; i++) {
        int a = pop(&s);
        int b = pop(&s);
        int next = a + b;
        push(&s, b);
        push(&s, a);
        push(&s, next);
    }

    printf("Fibonacci series up to %d terms: ", n);
    while (!isEmpty(&s)) {
        printf("%d ", pop(&s));
    }
    printf("\n");
}

int main() {
    int choice, number, terms;

    while (1) {
        printf("\n1. Factorial of a given number\n2. Generation of Fibonacci series\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a number to find its factorial: ");
                scanf("%d", &number);

                if (number < 0) {
                    printf("Factorial is not defined for negative numbers.\n");
                } else {
                    int result = factorial(number);
                    printf("Factorial of %d is %d\n", number, result);
                }
                break;

            case 2:
                printf("Enter the number of terms for the Fibonacci series: ");
                scanf("%d", &terms);

                generateFibonacci(terms);
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
