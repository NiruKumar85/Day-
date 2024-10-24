#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Adjacency List Node
struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
};

// Adjacency List
struct AdjList
{
    struct AdjListNode *head;
};

// Graph Structure
struct Graph
{
    int V;          // Number of vertices
    int isDirected; // Flag to indicate if the graph is directed or undirected
    struct AdjList *array;
};

// Create a new adjacency list node
struct AdjListNode *newAdjListNode(int dest)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
struct Graph *createGraph(int V, int isDirected)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->isDirected = isDirected;

    // Create an array of adjacency lists
    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; ++i)
    {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Add an edge to the graph
void addEdge(struct Graph *graph, int src, int dest)
{
    // Add an edge from src to dest (directed graph)
    struct AdjListNode *newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // If the graph is undirected, add an edge from dest to src
    if (!graph->isDirected)
    {
        newNode = newAdjListNode(src);
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
    }
}

// Display the graph as an adjacency list
void displayGraph(struct Graph *graph)
{
    for (int v = 0; v < graph->V; ++v)
    {
        struct AdjListNode *temp = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (temp)
        {
            printf("-> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Depth First Search (DFS) utility function
void DFSUtil(struct Graph *graph, int v, int visited[])
{
    visited[v] = 1;
    printf("%d ", v);

    struct AdjListNode *temp = graph->array[v].head;
    while (temp != NULL)
    {
        int connectedVertex = temp->dest;
        if (!visited[connectedVertex])
        {
            DFSUtil(graph, connectedVertex, visited);
        }
        temp = temp->next;
    }
}

// DFS traversal of the graph from a given vertex
void DFS(struct Graph *graph, int startVertex)
{
    int visited[MAX_VERTICES] = {0}; // Initialize visited array

    printf("DFS starting from vertex %d:\n", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
}

// Breadth First Search (BFS) of the graph
void BFS(struct Graph *graph, int startVertex)
{
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES], front = 0, rear = 0;

    // Mark the start vertex as visited and enqueue it
    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("BFS starting from vertex %d:\n", startVertex);

    while (front != rear)
    {
        int currentVertex = queue[front++]; // Dequeue
        printf("%d ", currentVertex);

        struct AdjListNode *temp = graph->array[currentVertex].head;
        while (temp)
        {
            int adjVertex = temp->dest;

            if (!visited[adjVertex])
            {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Check for connected components in an undirected graph using DFS
void findConnectedComponents(struct Graph *graph)
{
    int visited[MAX_VERTICES] = {0};
    int componentCount = 0;

    for (int v = 0; v < graph->V; ++v)
    {
        if (!visited[v])
        {
            printf("Connected Component %d: ", ++componentCount);
            DFSUtil(graph, v, visited);
            printf("\n");
        }
    }
}

// Utility function to detect cycle in an undirected graph using DFS
int isCyclicUtilUndirected(struct Graph *graph, int v, int visited[], int parent)
{
    visited[v] = 1;

    struct AdjListNode *temp = graph->array[v].head;
    while (temp)
    {
        int adjVertex = temp->dest;

        if (!visited[adjVertex])
        {
            if (isCyclicUtilUndirected(graph, adjVertex, visited, v))
                return 1;
        }
        else if (adjVertex != parent)
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

// Detect cycle in an undirected graph
int isCyclicUndirected(struct Graph *graph)
{
    int visited[MAX_VERTICES] = {0};

    for (int v = 0; v < graph->V; ++v)
    {
        if (!visited[v])
        {
            if (isCyclicUtilUndirected(graph, v, visited, -1))
                return 1;
        }
    }
    return 0;
}

int main()
{
    int V = 5;                               // Number of vertices
    struct Graph *graph = createGraph(V, 0); // Undirected graph

    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // Display the graph
    displayGraph(graph);

    // Perform DFS and BFS
    DFS(graph, 0);
    BFS(graph, 0);

    // Find connected components
    printf("\nConnected components in the graph:\n");
    findConnectedComponents(graph);

    // Check for cycle in an undirected graph
    if (isCyclicUndirected(graph))
    {
        printf("The graph contains a cycle.\n");
    }
    else
    {
        printf("The graph does not contain a cycle.\n");
    }

    return 0;
}
