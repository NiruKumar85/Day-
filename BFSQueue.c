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
    int V;
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
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists. Size of array will be V
    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; ++i)
    {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Add an edge to an undirected graph
void addEdge(struct Graph *graph, int src, int dest)
{
    // Add an edge from src to dest
    struct AdjListNode *newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since it's an undirected graph, add an edge from dest to src
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Queue structure
struct Queue
{
    int items[MAX_VERTICES];
    int front, rear;
};

// Create a queue
struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is empty
int isEmpty(struct Queue *queue)
{
    return queue->rear == -1;
}

// Enqueue an element to the queue
void enqueue(struct Queue *queue, int value)
{
    if (queue->rear == MAX_VERTICES - 1)
        printf("Queue is full\n");
    else
    {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Dequeue an element from the queue
int dequeue(struct Queue *queue)
{
    int item;
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        item = -1;
    }
    else
    {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear)
        {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// BFS algorithm using a queue
void BFS(struct Graph *graph, int startVertex)
{
    struct Queue *queue = createQueue();
    int *visited = (int *)malloc(graph->V * sizeof(int));

    // Initialize visited array to 0
    for (int i = 0; i < graph->V; i++)
    {
        visited[i] = 0;
    }

    // Mark the starting vertex as visited and enqueue it
    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    printf("BFS Traversal: ");

    while (!isEmpty(queue))
    {
        // Dequeue a vertex from queue and print it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        struct AdjListNode *temp = graph->array[currentVertex].head;
        while (temp)
        {
            int adjVertex = temp->dest;

            // If an adjacent vertex has not been visited, mark it as visited and enqueue it
            if (!visited[adjVertex])
            {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// Driver code
int main()
{
    int V = 6;
    struct Graph *graph = createGraph(V);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    printf("Breadth First Search starting from vertex 0:\n");
    BFS(graph, 0);

    return 0;
}
