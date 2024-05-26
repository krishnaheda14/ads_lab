#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

int comparator(const void* p1, const void* p2)
{
    const int (*x)[3] = p1;
    const int (*y)[3] = p2;

    return (*x)[2] - (*y)[2];
}

void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component] = findParent(parent, parent[component]);
}


void unionSet(int u, int v, int parent[], int rank[], int n)
{
    // Finding the parents
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if (rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[v] = u;

        rank[u]++;
    }
}


void kruskalAlgo(int n, int edge[][3])
{
    
    qsort(edge, n, sizeof(edge[0]), comparator);

    int parent[n];
    int rank[n];

    makeSet(parent, rank, n);

    int minCost = 0;

    printf("Following are the edges in the constructed MST\n");
    for (int i = 0; i < n; i++)
    {
        int v1 = findParent(parent, edge[i][0]);
        int v2 = findParent(parent, edge[i][1]);
        int wt = edge[i][2];

        
        if (v1 != v2)
        {
            unionSet(v1, v2, parent, rank, n);
            minCost += wt;
            printf("%d -- %d == %d\n", edge[i][0],
                   edge[i][1], wt);
        }
    }

    printf("Minimum Cost Spanning Tree: %d\n", minCost);
}

void createAdjacencyMatrix(int numVertices, int adjacencyMatrix[][MAX_VERTICES])
{
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
}

int main()
{
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    numEdges = numVertices * (numVertices - 1) / 2; // Assuming a complete graph

    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
    createAdjacencyMatrix(numVertices, adjacencyMatrix);

    int edge[numEdges][3];
    int edgeCount = 0;

    // Converting adjacency matrix to edge list
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = i + 1; j < numVertices; j++)
        {
            if (adjacencyMatrix[i][j] != 0)
            {
                edge[edgeCount][0] = i;
                edge[edgeCount][1] = j;
                edge[edgeCount][2] = adjacencyMatrix[i][j];
                edgeCount++;
            }
        }
    }

    kruskalAlgo(numEdges, edge);

    return 0;
}
