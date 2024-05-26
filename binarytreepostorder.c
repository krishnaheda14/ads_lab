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

// Function to perform non-recursive postorder traversal
void postorderTraversal(TreeNode* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    TreeNode* current = root;
    TreeNode* lastVisited = NULL;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = stack->top->node;
        if (current->right == NULL || current->right == lastVisited) {
            printf("%d ", current->data);
            pop(stack);
            lastVisited = current;
            current = NULL;
        } else {
            current = current->right;
        }
    }
    free(stack);
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

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
