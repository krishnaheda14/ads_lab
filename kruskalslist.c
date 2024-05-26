#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Node** head, int vertex, int weight) {
    Node* newNode = createNode(vertex, weight);
    newNode->next = *head;
    *head = newNode;
}

void printAdjacencyList(int numVertices, Node* adjacencyList[]) {
    for (int i = 0; i < numVertices; i++) {
        Node* current = adjacencyList[i];
        printf("Adjacency list for vertex %d: ", i);
        while (current != NULL) {
            printf("(%d, %d) ", current->vertex, current->weight);
            current = current->next;
        }
        printf("\n");
    }
}

void freeAdjacencyList(int numVertices, Node* adjacencyList[]) {
    for (int i = 0; i < numVertices; i++) {
        Node* current = adjacencyList[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

void createEdgeList(int numVertices, Node* adjacencyList[], int edge[][3], int *numEdges) {
    int edgeCount = 0;
    for (int i = 0; i < numVertices; i++) {
        Node* current = adjacencyList[i];
        while (current != NULL) {
            edge[edgeCount][0] = i;
            edge[edgeCount][1] = current->vertex;
            edge[edgeCount][2] = current->weight;
            edgeCount++;
            current = current->next;
        }
    }
    *numEdges = edgeCount;
}

int comparator(const void* p1, const void* p2) {
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;
    return (*x)[2] - (*y)[2];
}

int findParent(int parent[], int component) {
    if (parent[component] == component)
        return component;
    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[], int n) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskalAlgo(int numEdges, int edge[][3], int numVertices) {
    qsort(edge, numEdges, sizeof(edge[0]), comparator);

    int parent[numVertices];
    int rank[numVertices];
    int minCost = 0;

    for (int i = 0; i < numVertices; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < numEdges; i++) {
        int u = findParent(parent, edge[i][0]);
        int v = findParent(parent, edge[i][1]);
        int weight = edge[i][2];

        if (u != v) {
            printf("%d -- %d == %d\n", edge[i][0], edge[i][1], weight);
            minCost += weight;
            unionSet(u, v, parent, rank, numVertices);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

int main() {
    int numVertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    Node* adjacencyList[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjacencyList[i] = NULL;
        printf("Enter adjacency list for vertex %d (destination weight format) (-1 to terminate): ", i);
        int vertex, weight;
        while (true) {
            scanf("%d", &vertex);
            if (vertex == -1)
                break;
            scanf("%d", &weight);
            addEdge(&adjacencyList[i], vertex, weight);
        }
    }

    printAdjacencyList(numVertices, adjacencyList);

    int numEdges = numVertices * numVertices; // Max possible edges for a complete graph
    int edge[numEdges][3];
    int actualNumEdges;
    createEdgeList(numVertices, adjacencyList, edge, &actualNumEdges);

    kruskalAlgo(actualNumEdges, edge, numVertices);

    freeAdjacencyList(numVertices, adjacencyList);

    return 0;
}
