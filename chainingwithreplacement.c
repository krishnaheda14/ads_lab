#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // Define the size of the hash table
#define EMPTY -1      // Define the marker for empty slots

typedef struct {
    int data;
    int chain;
} HashEntry;

HashEntry hashTable[TABLE_SIZE];
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
        // If the current index contains an element with a different home position, replace it
        int currentIndex = index;
        int tempData = hashTable[currentIndex].data;
        int tempChain = hashTable[currentIndex].chain;

        if (hashFunction(tempData) != currentIndex) {
            hashTable[currentIndex].data = key;
            key = tempData;

            // Fix the chain of the displaced element
            int originalIndex = hashFunction(key);
            while (hashTable[originalIndex].chain != currentIndex) {
                originalIndex = hashTable[originalIndex].chain;
            }
            hashTable[originalIndex].chain = tempChain;
        }

        // Linear probing to find the next available slot
        while (hashTable[index].data != EMPTY) {
            index = (index + 1) % TABLE_SIZE;
        }
        
        // Insert the new key
        hashTable[index].data = key;

        // Update the chain for the original slot
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