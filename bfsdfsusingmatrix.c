#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];
int queue[MAX_VERTICES];
int front = -1, rear = -1;
int vertices;

void createGraph()
{
    int i, j;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix:\n");
    for (i = 0; i < vertices; i++)
    {
        printf("Enter adjacency for vertex %d: ", i);
        for (j = 0; j < vertices; j++)
        {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
}

void initializeVisited()
{
    int i;
    for (i = 0; i < vertices; i++)
    {
        visited[i] = 0;
    }
}

void enqueue(int vertex)
{
    if (rear == MAX_VERTICES - 1)
    {
        printf("Queue Overflow!\n");
    }
    else
    {
        if (front == -1)
        {
            front = 0;
        }
        rear++;
        queue[rear] = vertex;
    }
}

int dequeue()
{
    int vertex;
    if (front == -1 || front > rear)
    {
        printf("Queue Underflow!\n");
        return -1;
    }
    else
    {
        vertex = queue[front];
        front++;
        return vertex;
    }
}

int isQueueEmpty()
{
    if (front == -1 || front > rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void DFS(int vertex)
{
    int i;
    printf("%d ", vertex);
    visited[vertex] = 1;
    for (i = 0; i < vertices; i++)
    {
        if (adjacencyMatrix[vertex][i] == 1 && !visited[i])
        {
            DFS(i);
        }
    }
}

void BFS(int vertex)
{
    int i, dequeueVertex;
    printf("%d ", vertex);
    visited[vertex] = 1;
    enqueue(vertex);

    while (!isQueueEmpty())
    {
        dequeueVertex = dequeue();
        for (i = 0; i < vertices; i++)
        {
            if (adjacencyMatrix[dequeueVertex][i] == 1 && !visited[i])
            {
                printf("%d ", i);
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
}

int main()
{
    int choice, startVertex;

    while (1)
    {
        printf("\nMENU\n");
        printf("1. Create Graph\n");
        printf("2. DFS\n");
        printf("3. BFS\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createGraph();
            break;
        case 2:
            initializeVisited();
            printf("Enter the starting vertex for DFS: ");
            scanf("%d", &startVertex);
            printf("DFS Traversal: ");
            DFS(startVertex);
            printf("\n");
            break;
        case 3:
            initializeVisited();
            printf("Enter the starting vertex for BFS: ");
            scanf("%d", &startVertex);
            printf("BFS Traversal: ");
            BFS(startVertex);
            printf("\n");
            break;
        case 4:
            printf("Exiting program...\n");
            exit(0);
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
