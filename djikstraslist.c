#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define V 9

struct Node {
    int vertex, weight;
    struct Node* next;
};

void dijkstra(struct Node* adjList[], int src) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = -1;
        int min_dist = INT_MAX;


        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && dist[v] < min_dist) {
                u = v;
                min_dist = dist[v];
            }
        }

        if (u == -1)
            break;

        sptSet[u] = true;

        struct Node* current = adjList[u];
        while (current != NULL) {
            int v = current->vertex;
            int weight = current->weight;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
            current = current->next;
        }
    }

    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

struct Node* createNode(int v, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adjList[], int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = adjList[dest];
    adjList[dest] = newNode;
}

int main() {
    int numEdges;
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    struct Node* adjList[V];
    for (int i = 0; i < V; i++)
        adjList[i] = NULL;

    printf("Enter edges along with their weights (source destination weight):\n");
    int source, destination, weight;
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &source, &destination, &weight);
        addEdge(adjList, source, destination, weight);
    }

    dijkstra(adjList, 0);

    return 0;
}
