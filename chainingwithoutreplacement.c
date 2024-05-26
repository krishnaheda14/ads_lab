#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // Define the size of the hash table
#define EMPTY -1      // Define the marker for empty slots

struct HashEntry {
    int data;
    int chain;
};

struct HashEntry hashTable[TABLE_SIZE];
int collisionCount = 0;

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Initialize the hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].data = EMPTY;
        hashTable[i].chain = EMPTY;
    }
}

// Function to insert data into the hash table
void insert(int key) {
    int index = hashFunction(key);
    
    if (hashTable[index].data == EMPTY) {
        hashTable[index].data = key;
    } else {
        collisionCount++;
        int originalIndex = index;
        while (hashTable[index].data != EMPTY) {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                printf("Hash table is full!\n");
                return;
            }
        }
        // Insert the new key
        hashTable[index].data = key;
        
        // Update the chain
        int chainIndex = hashFunction(key);
        while (hashTable[chainIndex].chain != EMPTY) {
            chainIndex = hashTable[chainIndex].chain;
        }
        hashTable[chainIndex].chain = index;
    }
}

// Function to display the hash table
void displayTable() {
    printf("Index\tData\tChain\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%d\t%d\t%d\n", i, hashTable[i].data, hashTable[i].chain);
    }
}

int main() {
    int data, n;
    initializeTable();

    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data %d: ", i + 1);
        scanf("%d", &data);
        insert(data);
    }

    displayTable();
    printf("Number of collisions: %d\n", collisionCount);

    return 0;
}