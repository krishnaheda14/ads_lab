#include <stdio.h>
#include <stdlib.h>

#define MAX 3

typedef struct {
    int top1;
    int top2;
    int items[MAX];
} TwoStacks;

void initTwoStacks(TwoStacks *ts) {
    ts->top1 = -1;
    ts->top2 = MAX;
}

int isStack1Empty(TwoStacks *ts) {
    return ts->top1 == -1;
}

int isStack2Empty(TwoStacks *ts) {
    return ts->top2 == MAX;
}

int isStackFull(TwoStacks *ts) {
    return ts->top1 + 1 == ts->top2;
}

void pushStack1(TwoStacks *ts, int value) {
    if (isStackFull(ts)) {
        printf("Stack1 overflow\n");
        return;
    }
    ts->items[++ts->top1] = value;
}

void pushStack2(TwoStacks *ts, int value) {
    if (isStackFull(ts)) {
        printf("Stack2 overflow\n");
        return;
    }
    ts->items[--ts->top2] = value;
}

int popStack1(TwoStacks *ts) {
    if (isStack1Empty(ts)) {
        printf("Stack1 underflow\n");
        exit(1);
    }
    return ts->items[ts->top1--];
}

int popStack2(TwoStacks *ts) {
    if (isStack2Empty(ts)) {
        printf("Stack2 underflow\n");
        exit(1);
    }
    return ts->items[ts->top2++];
}

void displayStack1(TwoStacks *ts) {
    if (isStack1Empty(ts)) {
        printf("Stack1 is empty\n");
        return;
    }
    printf("Stack1 elements: ");
    for (int i = 0; i <= ts->top1; i++) {
        printf("%d ", ts->items[i]);
    }
    printf("\n");
}

void displayStack2(TwoStacks *ts) {
    if (isStack2Empty(ts)) {
        printf("Stack2 is empty\n");
        return;
    }
    printf("Stack2 elements: ");
    for (int i = MAX - 1; i >= ts->top2; i--) {
        printf("%d ", ts->items[i]);
    }
    printf("\n");
}

int main() {
    TwoStacks ts;
    initTwoStacks(&ts);

    int choice, value;
    while (1) {
        printf("\n1. Push to Stack1\n2. Push to Stack2\n3. Pop from Stack1\n4. Pop from Stack2\n");
        printf("5. Check if Stack is Full\n6. Check if Stack1 is Empty\n7. Check if Stack2 is Empty\n");
        printf("8. Display Stack1\n9. Display Stack2\n10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push to Stack1: ");
                scanf("%d", &value);
                pushStack1(&ts, value);
                break;
            case 2:
                printf("Enter value to push to Stack2: ");
                scanf("%d", &value);
                pushStack2(&ts, value);
                break;
            case 3:
                printf("Popped from Stack1: %d\n", popStack1(&ts));
                break;
            case 4:
                printf("Popped from Stack2: %d\n", popStack2(&ts));
                break;
            case 5:
                if (isStackFull(&ts)) {
                    printf("Both stacks are full\n");
                } else {
                    printf("Stacks are not full\n");
                }
                break;
            case 6:
                if (isStack1Empty(&ts)) {
                    printf("Stack1 is empty\n");
                } else {
                    printf("Stack1 is not empty\n");
                }
                break;
            case 7:
                if (isStack2Empty(&ts)) {
                    printf("Stack2 is empty\n");
                } else {
                    printf("Stack2 is not empty\n");
                }
                break;
            case 8:
                displayStack1(&ts);
                break;
            case 9:
                displayStack2(&ts);
                break;
            case 10:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
