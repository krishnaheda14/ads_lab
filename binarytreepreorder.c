#include <stdio.h>
#include <stdlib.h>

// Binary Tree Node
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Stack Node for non-recursive traversal
typedef struct StackNode {
    TreeNode* node;
    struct StackNode* next;
} StackNode;

// Stack to assist non-recursive traversal
typedef struct Stack {
    StackNode* top;
} Stack;

// Function to create a new tree node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to push a tree node onto the stack
void push(Stack* stack, TreeNode* node) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    newNode->node = node;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop a tree node from the stack
TreeNode* pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty\n");
        exit(1);
    }
    TreeNode* node = stack->top->node;
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return node;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// Function to insert a node into the BST
TreeNode* insertBST(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else {
        root->right = insertBST(root->right, data);
    }
    return root;
}

// Function to perform non-recursive preorder traversal
void preorderTraversal(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    TreeNode* current = root;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            printf("%d ", current->data);
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        current = current->right;
    }
    free(stack);
}

// Function to count leaf nodes in the binary tree
int countLeafNodes(TreeNode* root) {
    if (root == NULL)
        return 0;
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    TreeNode* current = root;
    int count = 0;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        if (current->left == NULL && current->right == NULL)
            count++;
        current = current->right;
    }
    free(stack);
    return count;
}

// Function to count total number of nodes in the binary tree
int countNodes(TreeNode* root) {
    if (root == NULL)
        return 0;
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    TreeNode* current = root;
    int count = 0;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
            count++;
        }
        current = pop(stack);
        current = current->right;
    }
    free(stack);
    return count;
}

// Function to find the height of the binary tree
int findHeight(TreeNode* root) {
    if (root == NULL)
        return 0;
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    TreeNode* current = root;
    int height = 0;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
            height++;
        }
        current = pop(stack);
        current = current->right;
    }
    free(stack);
    return height;
}

// Function to dynamically construct the BST
TreeNode* buildBST() {
    int n, data;
    TreeNode* root = NULL;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        root = insertBST(root, data);
    }

    return root;
}

int main() {
    TreeNode* root = buildBST();

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
    printf("Total Number of Nodes: %d\n", countNodes(root));
    printf("Height of the Tree: %d\n", findHeight(root));

    return 0;
}
