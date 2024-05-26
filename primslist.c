#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node** head;
    int vertices;
} Graph;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->head = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->head[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->head[src];
    graph->head[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->head[dest];
    graph->head[dest] = newNode;
}

int minKey(int key[], int mstSet[], int vertices) {
    int min = INT_MAX, minIndex;
    for (int v = 0; v < vertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printMST(int parent[], int vertices, Graph* graph) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        for (Node* node = graph->head[i]; node != NULL; node = node->next) {
            if (node->vertex == parent[i]) {
                printf("%d - %d \t%d \n", parent[i], i, node->weight);
                break;
            }
        }
    }
}

void primMST(Graph* graph) {
    int vertices = graph->vertices;
    int parent[vertices];
    int key[vertices];
    int mstSet[vertices];

    for (int i = 0; i < vertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minKey(key, mstSet, vertices);
        mstSet[u] = 1;

        for (Node* node = graph->head[u]; node != NULL; node = node->next) {
            int v = node->vertex;
            if (mstSet[v] == 0 && node->weight < key[v]) {
                parent[v] = u;
                key[v] = node->weight;
            }
        }
    }

    printMST(parent, vertices, graph);
}

int main() {
    int vertices, edges;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    Graph* graph = createGraph(vertices);

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        if (src >= vertices || dest >= vertices || src < 0 || dest < 0) {
            printf("Invalid edge!\n");
            i--;
        } else {
            addEdge(graph, src, dest, weight);
        }
    }

    primMST(graph);

    for (int i = 0; i < vertices; i++) {
        Node* node = graph->head[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->head);
    free(graph);

    return 0;
}
