#include <stdio.h>
#include <stdlib.h>

// Node structure for the Inorder Threaded Binary Tree
typedef struct TBTNode {
    int data;
    struct TBTNode *left, *right;
    int ltag, rtag; // Tags to indicate if left and right pointers are threads
} TBTNode;

// Function to create a new node
TBTNode* createNode(int data) {
    TBTNode* newNode = (TBTNode*)malloc(sizeof(TBTNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->ltag = 1;
    newNode->rtag = 1;
    return newNode;
}

// Function to insert a node in the Inorder Threaded Binary Tree
TBTNode* insertNode(TBTNode* root, int data) {
    TBTNode *ptr = root, *parent = NULL;

    // Find the position where the new node will be inserted
    while (ptr != NULL) {
        if (data == ptr->data) {
            printf("Duplicate data not allowed.\n");
            return root;
        }
        parent = ptr;
        if (data < ptr->data) {
            if (ptr->ltag == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rtag == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    // Create the new node
    TBTNode* newNode = createNode(data);

    if (parent == NULL) {
        root = newNode;
        newNode->left = NULL;
        newNode->right = NULL;
    } else if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->ltag = 0;
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->left = parent;
        parent->rtag = 0;
        parent->right = newNode;
    }

    return root;
}

// Function to find the next node in preorder traversal
TBTNode* preorderSuccessor(TBTNode* node) {
    if (node->ltag == 0)
        return node->left;
    while (node->rtag == 1 && node->right != NULL)
        node = node->right;
    return node->right;
}

// Function to perform preorder traversal of the Inorder Threaded Binary Tree
void preorderTraversal(TBTNode* root) {
    if (root == NULL)
        return;

    TBTNode* cur = root;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = preorderSuccessor(cur);
    }
}

// Main function to execute the program
int main() {
    TBTNode* root = NULL;

    int n, data;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    printf("Preorder traversal of the Inorder Threaded Binary Tree:\n");
    preorderTraversal(root);

    return 0;
}
