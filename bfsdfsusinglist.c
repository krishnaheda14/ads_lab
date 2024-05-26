#include <stdio.h>
#include <stdlib.h>

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

   
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void DFS(struct Graph* graph, int start) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    int stack[graph->V];
    int top = -1;

    visited[start] = 1;
    stack[++top] = start;

    while (top != -1) {
        int current = stack[top--];
        printf("%d ", current);

        struct AdjListNode* temp = graph->array[current].head;
        while (temp != NULL) {
            if (!visited[temp->dest]) {
                visited[temp->dest] = 1;
                stack[++top] = temp->dest;
            }
            temp = temp->next;
        }
    }

    free(visited);
}

void BFS(struct Graph* graph, int start) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    int queue[graph->V];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        struct AdjListNode* temp = graph->array[current].head;
        while (temp != NULL) {
            if (!visited[temp->dest]) {
                visited[temp->dest] = 1;
                queue[rear++] = temp->dest;
            }
            temp = temp->next;
        }
    }

    free(visited);
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Add Edge\n");
    printf("2. Depth First Search (DFS)\n");
    printf("3. Breadth First Search (BFS)\n");
    printf("4. Exit\n");
}

int main() {
    int V, choice, src, dest;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source and destination vertices (0 to %d): ", V - 1);
                scanf("%d %d", &src, &dest);
                if (src >= 0 && src < V && dest >= 0 && dest < V)
                    addEdge(graph, src, dest);
                else
                    printf("Invalid vertices! Please enter vertices within the range.\n");
                break;
            case 2:
                printf("DFS Traversal: ");
                DFS(graph, 0);
                printf("\n");
                break;
            case 3:
                printf("BFS Traversal: ");
                BFS(graph, 0);
                printf("\n");
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
