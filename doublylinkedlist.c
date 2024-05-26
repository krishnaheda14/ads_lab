#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}

void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void insertAfter(Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }
    prevNode->next = newNode;
    newNode->prev = prevNode;
}

void deleteNode(Node** head, Node* delNode) {
    if (*head == NULL || delNode == NULL) {
        printf("List is empty or node to be deleted is NULL\n");
        return;
    }
    if (*head == delNode) {
        *head = delNode->next;
    }
    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }
    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }
    free(delNode);
}

void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty, cannot delete\n");
        return;
    }
    deleteNode(head, *head);
}

void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty, cannot delete\n");
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    deleteNode(head, temp);
}

void display(Node* head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int getIntInput() {
    int value;
    while (scanf("%d", &value) != 1) {
        while (getchar() != '\n'); // Clear invalid input
        printf("Invalid input. Please enter an integer: ");
    }
    return value;
}

int main() {
    Node* head = NULL;

    int choice, data, position;
    Node* temp;

    while (1) {
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert after a node\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete a specific node\n");
        printf("7. Display list\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        choice = getIntInput();

        switch (choice) {
            case 1:
                printf("Enter data to insert at the beginning: ");
                data = getIntInput();
                insertAtBeginning(&head, data);
                break;
            case 2:
                printf("Enter data to insert at the end: ");
                data = getIntInput();
                insertAtEnd(&head, data);
                break;
            case 3:
                printf("Enter data to insert: ");
                data = getIntInput();
                printf("Enter the data of the node after which to insert: ");
                position = getIntInput();
                temp = head;
                while (temp != NULL && temp->data != position) {
                    temp = temp->next;
                }
                if (temp == NULL) {
                    printf("Node with given data not found\n");
                } else {
                    insertAfter(temp, data);
                }
                break;
            case 4:
                deleteFromBeginning(&head);
                break;
            case 5:
                deleteFromEnd(&head);
                break;
            case 6:
                printf("Enter the data of the node to delete: ");
                data = getIntInput();
                temp = head;
                while (temp != NULL && temp->data != data) {
                    temp = temp->next;
                }
                if (temp == NULL) {
                    printf("Node with given data not found\n");
                } else {
                    deleteNode(&head, temp);
                }
                break;
            case 7:
                display(head);
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
