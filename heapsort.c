#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char student_name[50];
    int student_roll_no;
    float total_marks;
} Student;

int swap_count = 0;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

void heapify(Student arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no) {
        largest = left;
    }

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(Student arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int rollNoExists(Student arr[], int size, int roll_no) {
    for (int i = 0; i < size; i++) {
        if (arr[i].student_roll_no == roll_no) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    printf("Enter the number of students: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    Student *arr = (Student *)malloc(n * sizeof(Student));
    if (arr == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d\n", i + 1);
        printf("Name: ");
        scanf("%s", arr[i].student_name);
        printf("Student Roll Number: ");
        int roll_no;
        while (1) {
            if (scanf("%d", &roll_no) != 1) {
                printf("Invalid input for student roll number. Try again: ");
                while (getchar() != '\n'); // Clear invalid input
            } else if (rollNoExists(arr, i, roll_no)) {
                printf("Student roll number already exists. Enter a unique student roll number: ");
            } else {
                arr[i].student_roll_no = roll_no;
                break;
            }
        }
        printf("Total Marks: ");
        if (scanf("%f", &arr[i].total_marks) != 1) {
            printf("Invalid input for total marks.\n");
            free(arr);
            return 1;
        }
    }

    heapSort(arr, n);

    printf("Sorted list of students based on student roll number:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Student Roll Number: %d, Total Marks: %.2f\n",
               arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }

    printf("Number of swaps performed: %d\n", swap_count);

    free(arr);
    return 0;
}
