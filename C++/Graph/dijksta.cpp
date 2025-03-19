#include <iostream>
using namespace std;

class MinHeapNode
{
public:
    int vertex;
    int distance;

    MinHeapNode(int vertex, int distance)
    {
        this->vertex = vertex;
        this->distance = distance;
    }
};

class MinHeap
{
    MinHeapNode **heap;
    int *pos;
    int size;
    int capacity;

public:
    MinHeap(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        heap = new MinHeapNode *[capacity];
        pos = new int[capacity];

        for (int i = 0; i < capacity; i++)
        {
            pos[i] = -1;
        }
    }

    void swapNode(int i, int j)
    {
        pos[heap[i]->vertex] = j;
        pos[heap[j]->vertex] = i;
        swap(heap[i], heap[j]);
    }

    int getParentIdx(int i)
    {
        return (i - 1) / 2;
    }

    int leftChildIdx(int i)
    {
        return 2 * i + 1;
    }

    int rightChildIdx(int i)
    {
        return 2 * i + 2;
    }

    void push(int vertex, int distance)
    {
        MinHeapNode *newNode = new MinHeapNode(vertex, distance);
        size++;
        int lastIdx = size - 1;
        heap[lastIdx] = newNode;
        pos[vertex] = lastIdx;

        int parentIdx = getParentIdx(lastIdx);
        while (lastIdx != 0 && heap[parentIdx]->distance > heap[lastIdx]->distance)
        {
            swapNode(lastIdx, parentIdx);
            lastIdx = getParentIdx(lastIdx);
        }
    }

    MinHeapNode *pop()
    {
        if (size == 0)
            return nullptr;

        MinHeapNode *root = heap[0];
        heap[0] = heap[size - 1];
        pos[heap[0]->vertex] = 0;
        size--;
        heapify(0);

        return root;
    }

    void heapify(int i)
    {
        int smallest = i;
        int leftChild = leftChildIdx(i);
        int rightChild = rightChildIdx(i);

        if (leftChild < size && heap[leftChild]->distance < heap[smallest]->distance)
        {
            smallest = leftChild;
        }

        if (rightChild < size && heap[rightChild]->distance < heap[smallest]->distance)
        {
            smallest = rightChild;
        }

        if (smallest != i)
        {
            swapNode(i, smallest);
            heapify(smallest);
        }
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void decreaseKey(int vertex, int newDist)
    {
        int i = pos[vertex];
        heap[i]->distance = newDist;

        while (i != 0 && heap[getParentIdx(i)]->distance > heap[i]->distance)
        {
            swapNode(i, getParentIdx(i));
            i = getParentIdx(i);
        }
    }

    bool isInMinHeap(int vertex)
    {
        return pos[vertex] < size && pos[vertex] != -1;
    }

    void display()
    {
        for (int i = 0; i < size; i++)
        {
            cout << heap[i] << " ";
        }

        cout << endl;
    }
};

class Node
{
public:
    int vertex, weight;
    Node *next;

    Node(int vertex, int weight)
    {
        this->vertex = vertex;
        this->weight = weight;
        this->next = NULL;
    }
};

class LinkedList
{
public:
    Node *head = NULL;
    Node *tail = NULL;

    void addNodeLast(int vertex, int weight)
    {
        Node *newNode = new Node(vertex, weight);
        if (head == NULL)
        {
            head = tail = newNode;
            return;
        }

        tail->next = newNode;
        tail = newNode;
    }

    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << "(" << temp->vertex << ", " << temp->weight << ") ";
            temp = temp->next;
        }
    }
};

class Graph
{
    int V;
    LinkedList *adjList;

public:
    Graph(int V)
    {
        this->V = V;

        adjList = new LinkedList[V];
    }

    void addEdge(int u, int v, int weight)
    {
        if (u >= V || v >= V)
        {
            cout << "Invalid Edge" << endl;
            return;
        }

        adjList[u].addNodeLast(v, weight);
        // adjList[v].addEdge(u, weight); // For undirected graph
    }

    void dijkstra(int src)
    {
        int *dist = new int[V];
        for (int i = 0; i < V; i++)
            dist[i] = INT32_MAX;

        MinHeap minHeap(V);
        minHeap.push(src, 0);
        dist[src] = 0;

        while (!minHeap.isEmpty())
        {
            MinHeapNode *minNode = minHeap.pop();
            int u = minNode->vertex;
            delete minNode;

            Node *temp = adjList[u].head;
            while (temp != NULL)
            {
                int v = temp->vertex;
                int weight = temp->weight;

                if (dist[u] != INT32_MAX && dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;

                    if (minHeap.isInMinHeap(v))
                    {
                        minHeap.decreaseKey(v, dist[v]);
                    }
                    else
                    {
                        minHeap.push(v, dist[v]);
                    }
                }

                temp = temp->next;
            }
        }

        cout << "Vertex\tDistance from Source\n";
        for (int i = 0; i < V; i++)
        {
            cout << i << "\t" << dist[i] << endl;
        }

        delete[] dist;
    }

    void display()
    {
        for (int i = 0; i < V; i++)
        {
            Node *temp = adjList[i].head;
            if (temp == NULL)
            {
                continue;
            }

            cout << i << " -> ";
            adjList[i].display();
            cout << endl;
        }
    }
};

int main()
{
    int Vertices, Edges;
    cout << "Enter Vertices and Edge : ";
    cin >> Vertices >> Edges;

    Graph g(Vertices);
    for (int i = 0; i < Edges; i++)
    {
        int u, v, wt;
        cout << "Enter u, v and wt : ";
        cin >> u >> v >> wt;
        g.addEdge(u, v, wt);
    }

    cout << "Graph : " << endl;
    g.display();
    cout << endl;

    int src;
    cout << "Enter Source : ";
    cin >> src;
    g.dijkstra(src);

    return 0;
}