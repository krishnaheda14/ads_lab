#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int front1, rear1;
    int front2, rear2;
    int items[MAX];
} TwoQueues;

void initTwoQueues(TwoQueues *q) {
    q->front1 = -1;
    q->rear1 = -1;
    q->front2 = MAX;
    q->rear2 = MAX;
}

int isFull1(TwoQueues *q) {
    return q->rear1 + 1 == q->front2;
}

int isFull2(TwoQueues *q) {
    return q->rear2 - 1 == q->rear1;
}

int isEmpty1(TwoQueues *q) {
    return q->front1 == -1;
}

int isEmpty2(TwoQueues *q) {
    return q->front2 == MAX;
}

void addq1(TwoQueues *q, int value) {
    if (isFull1(q)) {
        printf("Queue1 overflow\n");
        return;
    }
    if (q->front1 == -1) {
        q->front1 = 0;
    }
    q->items[++q->rear1] = value;
}

void addq2(TwoQueues *q, int value) {
    if (isFull2(q)) {
        printf("Queue2 overflow\n");
        return;
    }
    if (q->front2 == MAX) {
        q->front2 = MAX - 1;
    }
    q->items[--q->rear2] = value;
}

int delq1(TwoQueues *q) {
    if (isEmpty1(q)) {
        printf("Queue1 underflow\n");
        exit(1);
    }
    int value = q->items[q->front1];
    if (q->front1 == q->rear1) {
        q->front1 = -1;
        q->rear1 = -1;
    } else {
        q->front1++;
    }
    return value;
}

int delq2(TwoQueues *q) {
    if (isEmpty2(q)) {
        printf("Queue2 underflow\n");
        exit(1);
    }
    int value = q->items[q->front2];
    if (q->front2 == q->rear2) {
        q->front2 = MAX;
        q->rear2 = MAX;
    } else {
        q->front2--;
    }
    return value;
}

void displayQueue1(TwoQueues *q) {
    if (isEmpty1(q)) {
        printf("Queue1 is empty\n");
        return;
    }
    printf("Queue1 elements: ");
    for (int i = q->front1; i <= q->rear1; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

void displayQueue2(TwoQueues *q) {
    if (isEmpty2(q)) {
        printf("Queue2 is empty\n");
        return;
    }
    printf("Queue2 elements: ");
    for (int i = q->front2; i >= q->rear2; i--) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main() {
    TwoQueues q;
    initTwoQueues(&q);

    int choice, value, queueNumber;
    while (1) {
        printf("\n1. Add to Queue\n2. Delete from Queue\n3. Display Queue\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &queueNumber);
                printf("Enter value to add: ");
                scanf("%d", &value);
                if (queueNumber == 1) {
                    addq1(&q, value);
                } else if (queueNumber == 2) {
                    addq2(&q, value);
                } else {
                    printf("Invalid queue number\n");
                }
                break;
            case 2:
                printf("Enter queue number (1 or 2): ");
                scanf("%d", &queueNumber);
                if (queueNumber == 1) {
                    printf("Deleted from Queue1: %d\n", delq1(&q));
                } else if (queueNumber == 2) {
                    printf("Deleted from Queue2: %d\n", delq2(&q));
                } else {
                    printf("Invalid queue number\n");
                }
                break;
            case 3:
                printf("Enter queue number (1 or 2) to display: ");
                scanf("%d", &queueNumber);
                if (queueNumber == 1) {
                    displayQueue1(&q);
                } else if (queueNumber == 2) {
                    displayQueue2(&q);
                } else {
                    printf("Invalid queue number\n");
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
