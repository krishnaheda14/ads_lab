#include <stdio.h>

void findSwappedElements(int arr[], int n) {
    int x = -1, y = -1; 
    int i;

    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            x = arr[i];
            break;
        }
    }

    for (i = n - 1; i > 0; i--) {
        if (arr[i] < arr[i - 1]) {
            y = arr[i];
            break;
        }
    }

    int posX = -1, posY = -1;
    for (i = 0; i < n; i++) {
        if (arr[i] == x) {
            posX = i;
        } else if (arr[i] == y) {
            posY = i;
        }
    }

    // Print the result
    if (posX != -1 && posY != -1) {
        printf("The swapped elements are %d and %d\n", x, y);
        printf("Their positions are %d and %d\n", posX, posY);
    } else {
        printf("No swapped elements found.\n");
    }
}

int main() {
    int n, i;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findSwappedElements(arr, n);

    return 0;
}