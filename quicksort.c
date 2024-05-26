#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char employee_name[50];
    int emp_no;
    float emp_salary;
} Employee;

int swap_count = 0;

void swap(Employee *a, Employee *b) {
    Employee temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

int partition(Employee arr[], int low, int high) {
    int pivot = arr[high].emp_no;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].emp_no < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Employee arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int empNoExists(Employee arr[], int size, int emp_no) {
    for (int i = 0; i < size; i++) {
        if (arr[i].emp_no == emp_no) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int n;
    printf("Enter the number of employees: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    Employee *arr = (Employee *)malloc(n * sizeof(Employee));
    if (arr == NULL) {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter details for employee %d\n", i + 1);
        printf("Name: ");
        scanf("%s", arr[i].employee_name);
        printf("Employee Number: ");
        int emp_no;
        while (1) {
            if (scanf("%d", &emp_no) != 1) {
                printf("Invalid input for employee number. Try again: ");
                while (getchar() != '\n'); // Clear invalid input
            } else if (empNoExists(arr, i, emp_no)) {
                printf("Employee number already exists. Enter a unique employee number: ");
            } else {
                arr[i].emp_no = emp_no;
                break;
            }
        }
        printf("Salary: ");
        if (scanf("%f", &arr[i].emp_salary) != 1) {
            printf("Invalid input for salary.\n");
            free(arr);
            return 1;
        }
    }

    quickSort(arr, 0, n - 1);

    printf("Sorted list of employees based on employee number:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Employee Number: %d, Salary: %.2f\n",
               arr[i].employee_name, arr[i].emp_no, arr[i].emp_salary);
    }

    printf("Number of swaps performed: %d\n", swap_count);

    free(arr);
    return 0;
}
