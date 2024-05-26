#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node *next;
} Node;

Node* createNode(int coeff, int exp) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

void append(Node **poly, int coeff, int exp) {
    Node *newNode = createNode(coeff, exp);
    if (*poly == NULL) {
        *poly = newNode;
        return;
    }
    Node *temp = *poly;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void display(Node *poly) {
    if (poly == NULL) {
        printf("0\n");
        return;
    }
    Node *temp = poly;
    while (temp != NULL) {
        if (temp->coeff > 0 && temp != poly) {
            printf(" + ");
        }
        if (temp->exp == 0) {
            printf("%d", temp->coeff);
        } else {
            printf("%dx^%d", temp->coeff, temp->exp);
        }
        temp = temp->next;
    }
    printf("\n");
}

Node* addPolynomials(Node *poly1, Node *poly2) {
    Node *result = NULL;
    Node *temp1 = poly1, *temp2 = poly2;

    while (temp1 != NULL && temp2 != NULL) {
        if (temp1->exp > temp2->exp) {
            append(&result, temp1->coeff, temp1->exp);
            temp1 = temp1->next;
        } else if (temp1->exp < temp2->exp) {
            append(&result, temp2->coeff, temp2->exp);
            temp2 = temp2->next;
        } else {
            int sumCoeff = temp1->coeff + temp2->coeff;
            if (sumCoeff != 0) {
                append(&result, sumCoeff, temp1->exp);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }

    while (temp1 != NULL) {
        append(&result, temp1->coeff, temp1->exp);
        temp1 = temp1->next;
    }

    while (temp2 != NULL) {
        append(&result, temp2->coeff, temp2->exp);
        temp2 = temp2->next;
    }

    return result;
}

int getIntInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n'); 
        printf("Invalid input. Please enter an integer: ");
    }
    return value;
}

void readPolynomial(Node **poly) {
    int n, coeff, exp;
    printf("Enter the number of terms in the polynomial: ");
    n = getIntInput();
    for (int i = 0; i < n; i++) {
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        coeff = getIntInput();
        exp = getIntInput();
        append(poly, coeff, exp);
    }
}

int main() {
    Node *poly1 = NULL;
    Node *poly2 = NULL;

    printf("Enter the first polynomial:\n");
    readPolynomial(&poly1);

    printf("Enter the second polynomial:\n");
    readPolynomial(&poly2);

    printf("First polynomial: ");
    display(poly1);

    printf("Second polynomial: ");
    display(poly2);

    Node *sum = addPolynomials(poly1, poly2);

    printf("Sum of polynomials: ");
    display(sum);

    return 0;
}
