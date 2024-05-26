#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void display(Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void Reverse(Node **head) {
    if (*head == NULL) {
        printf("List is empty, nothing to reverse\n");
        return;
    }

    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;

    while (current != NULL) {
        next = current->next; 
        current->next = prev; 
        prev = current;       
        current = next;
    }

    *head = prev; 
}
int getIntInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n'); 
        printf("Invalid input. Please enter an integer: ");
    }
    return value;
}

void readList(Node **head) {
    int n, data;
    printf("Enter the number of elements in the list: ");
    n = getIntInput();
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        data = getIntInput();
        append(head, data);
    }
}

int main() {
    Node *head = NULL;

    printf("Enter the elements of the list:\n");
    readList(&head);

    printf("Original list: ");
    display(head);

    Reverse(&head);

    printf("Reversed list: ");
    display(head);

    return 0;
}
