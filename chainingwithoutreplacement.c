#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Node structure for chaining
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Hash table entry
typedef struct HashTableEntry {
    int data;
    Node* chain;
    int isOccupied;
} HashTableEntry;

HashTableEntry hashTable[TABLE_SIZE];

// Function to create a new node for chaining
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hash function
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

int insert(int key) {
    int hashIndex = hashFunction(key);
    int originalIndex = hashIndex;
    int collisions = 0;

    // Linear probing to find an empty slot or the slot with the same key
    while (hashTable[hashIndex].isOccupied && hashTable[hashIndex].data != key) {
        hashIndex = (hashIndex + 1) % TABLE_SIZE;
        collisions++;
        // Check if we've gone through the whole table
        if (hashIndex == originalIndex) {
            printf("Hash table is full. Cannot insert key %d\n", key);
            return -1;
        }
    }

    // Insert into the hash table if it's empty
    if (!hashTable[hashIndex].isOccupied) {
        hashTable[hashIndex].data = key;
        hashTable[hashIndex].chain = NULL;
        hashTable[hashIndex].isOccupied = 1;
    } else {
        // Chain the element to the existing entry
        Node* newNode = createNode(key);
        Node* current = hashTable[hashIndex].chain;
        if (current == NULL) {
            hashTable[hashIndex].chain = newNode;
        } else {
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    return collisions;
}

// Function to display the hash table
void displayHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        if (hashTable[i].isOccupied) {
            printf("%d", hashTable[i].data);
            Node* current = hashTable[i].chain;
            while (current != NULL) {
                printf(" -> %d", current->data);
                current = current->next;
            }
        }
        printf("\n");
    }
}

int main() {
    // Initialize the hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].isOccupied = 0;
        hashTable[i].chain = NULL;
    }

    int n, key, totalCollisions = 0;
    printf("Enter the number of keys to be inserted: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter key %d: ", i + 1);
        scanf("%d", &key);
        int collisions = insert(key);
        if (collisions != -1) {
            printf("Number of collisions while inserting key %d: %d\n", key, collisions);
            totalCollisions += collisions;
        }
    }

    printf("\nHash Table:\n");
    displayHashTable();

    printf("\nTotal number of collisions: %d\n", totalCollisions);

    return 0;
}
