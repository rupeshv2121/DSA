// #include <iostream>
// #include <unordered_map>
// #include <list>
// #include <queue>
// #include <stack>
// using namespace std;

// class graph
// {
// public:
//     unordered_map<int, list<int>> adj;

//     void addEdge(int u, int v, bool direction)
//     {
//         // direc -> 0 for undirected
//         // direc -> 1 for directed

//         adj[u].push_back(v);
//         // if (direction == 0)
//         // {
//         //     adj[v].push_back(u);
//         // }
//     }

//     void bfs(int src)
//     {
//         unordered_map<int, bool> visited;
//         queue<int> q;

//         q.push(src);
//         visited[src] = true;

//         while (!q.empty())
//         {
//             int currNode = q.front();
//             cout << currNode << " -> ";
//             q.pop();

//             for (auto neighbor : adj[currNode])
//             {
//                 if (!visited[neighbor])
//                 {
//                     visited[neighbor] = true;
//                     q.push(neighbor);
//                 }
//             }
//         }
//         cout << "END" << endl;
//     }

//     void dfs(int src, unordered_map<int, bool> &visited)
//     {
//         cout << src << " -> ";
//         visited[src] = true;

//         for (auto i : adj[src])
//         {
//             if (!visited[i])
//             {
//                 dfs(i, visited);
//             }
//         }
//     }

//     bool isCycleBFS(int src, unordered_map<int, bool> &visited)
//     {
//         unordered_map<int, int> parent;
//         visited[src] = true;
//         parent[src] = -1;

//         queue<int> q;
//         q.push(src);

//         while (!q.empty())
//         {
//             int currNode = q.front();
//             q.pop();

//             for (auto i : adj[currNode])
//             {
//                 if (visited[i] == true && i != parent[currNode])
//                 {
//                     return true;
//                 }
//                 else if (!visited[i])
//                 {
//                     visited[i] = true;
//                     q.push(i);
//                     parent[i] = currNode;
//                 }
//             }
//         }

//         return false;
//     }

//     bool hasCycleBFS()
//     {
//         unordered_map<int, bool> visited;
//         for (auto node : adj)
//         {
//             if (!visited[node.first])
//             {
//                 if (isCycleBFS(node.first, visited))
//                 {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }

//     bool isCycleDFS(int src, unordered_map<int, bool> &visited, int parent)
//     {
//         visited[src] = true;

//         for (auto i : adj[src])
//         {
//             if (!visited[i])
//             {
//                 bool cycleDetected = isCycleDFS(i, visited, src);
//                 if (cycleDetected)
//                 {
//                     return true;
//                 }
//             }
//             else if (i != parent)
//             {
//                 return true;
//             }
//         }

//         return false;
//     }

//     bool hasCycleDFS()
//     {
//         unordered_map<int, bool> visited;
//         for (auto node : adj)
//         {
//             if (!visited[node.first])
//             {
//                 if (isCycleDFS(node.first, visited, -1))
//                 {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }

//     bool isCycleDFS(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &recStack)
//     {
//         visited[node] = true;
//         recStack[node] = true;

//         for (auto neighbor : adj[node])
//         {
//             if (!visited[neighbor] && isCycleDFS(neighbor, visited, recStack))
//                 return true;
//             else if (recStack[neighbor])
//                 return true;
//         }

//         recStack[node] = false;
//         return false;
//     }

//     bool hasCycleDirected()
//     {
//         unordered_map<int, bool> visited;
//         unordered_map<int, bool> recStack;

//         for (auto node : adj)
//         {
//             if (!visited[node.first])
//             {
//                 if (isCycleDFS(node.first, visited, recStack))
//                     return true;
//             }
//         }
//         return false;
//     }

//     void topoSort(unordered_map<int, bool> &visited, stack<int> &s, int src)
//     {
//         visited[src] = true;

//         for (auto i : adj[src])
//         {
//             if (!visited[i])
//             {
//                 topoSort(visited, s, i);
//             }
//         }

//         s.push(src);
//     }

//     void callTopoSort()
//     {
//         if (hasCycleDirected())
//         {
//             cout << "Cycle detected! Topological sorting is not possible." << endl;
//             return;
//         }

//         unordered_map<int, bool> visited;
//         stack<int> s;
//         for (auto i : adj)
//         {
//             if (!visited[i.first])
//             {
//                 topoSort(visited, s, i.first);
//             }
//         }

//         cout << "Topological Order: ";
//         while (!s.empty())
//         {
//             cout << s.top() << " ";
//             s.pop();
//         }
//         cout << endl;
//     }

//     void printAdjList()
//     {
//         for (auto i : adj)
//         {
//             cout << i.first << " -> ";
//             for (auto j : i.second)
//             {
//                 cout << j << " ";
//             }
//             cout << endl;
//         }
//     }
// };

// int main()
// {
//     int n;
//     cout << "Enter number of nodes : ";
//     cin >> n;

//     cout << endl;

//     int m;
//     cout << "Enter number of edges : ";
//     cin >> m;

//     graph g;

//     for (int i = 0; i < m; i++)
//     {
//         int u, v;
//         cout << "Enter nodes : ";
//         cin >> u >> v;

//         // adding edges
//         g.addEdge(u, v, 0);
//     }

//     unordered_map<int, bool> visited;

//     // int startNode;
//     // cout << "Enter the Starting Node : ";
//     // cin >> startNode;
//     // g.bfs(startNode);

//     // // unordered_map<int, bool> vis;
//     // cout << "Enter the starting Node : ";
//     // cin >> startNode;
//     // g.dfs(startNode, visited);
//     // cout << "END" << endl;

//     // cout << "is cycle present by BFS ? " << g.hasCycleBFS() << endl;
//     // cout << "is cycle present by DFS ? " << g.hasCycleDFS() << endl;

//     g.callTopoSort();

//     // printing graph
//     // g.printAdjList();

//     return 0;
// }
#include <iostream>
using namespace std;

class stackNode
{
public:
    int data;
    stackNode *next;

    stackNode(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class Stack
{
    stackNode *top = NULL;

public:
    void push(int data)
    {
        stackNode *newNode = new stackNode(data);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (top == NULL)
        {
            return;
        }

        stackNode *temp = top;
        top = top->next;
        delete temp;
    }

    int peek()
    {
        if (top == NULL)
        {
            cout << "Stack is empyt" << endl;
            return -1;
        }

        return top->data;
    }

    bool isEmpty()
    {
        return top == nullptr;
    }
};

class QueueNode
{
public:
    int data;
    QueueNode *next;

    QueueNode(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class Queue
{
    QueueNode *rear = NULL;
    QueueNode *front = NULL;

public:
    void push(int data)
    {
        QueueNode *newNode = new QueueNode(data);
        if (front == NULL)
        {
            front = rear = newNode;
            return;
        }

        rear->next = newNode;
        rear = newNode;
    }

    void pop()
    {
        if (front == NULL)
        {
            return;
        }

        if (front == rear)
        {

            delete front;
            front = rear = NULL;
            return;
        }

        QueueNode *temp = front;
        front = front->next;
        delete temp;

        if (front == NULL)
        {
            rear = NULL;
        }
    }

    int top()
    {
        if (front == NULL)
        {
            cout << "Queue is empty!\n";
            return -1;
        }
        return front->data;
    }

    bool empty()
    {
        return front == NULL;
    }
};

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class LinkedList
{
    Node *tail = NULL;

public:
    Node *head = NULL;
    void addLast(int data)
    {
        Node *newNode = new Node(data);
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
        if (!temp)
        {
            cout << "No edges";
        }

        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

class Graph
{
    int V;
    int **adjMat;
    LinkedList *adjList;

public:
    Graph(int V)
    {
        this->V = V;

        adjMat = new int *[V];
        for (int i = 0; i < V; i++)
        {
            adjMat[i] = new int[V];
            for (int j = 0; j < V; j++)
            {
                adjMat[i][j] = 0;
            }
        }

        adjList = new LinkedList[V];
    }

    void addEdge(int u, int v)
    {
        if (u >= V || v >= V)
        {
            cout << "Invalid edge: " << u << " -> " << v << endl;
            return;
        }

        // addition of node into matrix
        adjMat[u][v] = 1;

        // addition of node into list
        adjList[u].addLast(v);
    }

    void bfs(int src)
    {
        bool *visited = new bool[V]();

        Queue q;
        q.push(src);
        visited[src] = true;

        while (!q.empty())
        {
            int currNode = q.top();
            q.pop();
            cout << currNode << " ";

            Node *temp = adjList[currNode].head;
            while (temp != NULL)
            {
                int neighbour = temp->data;

                if (!visited[neighbour])
                {
                    q.push(neighbour);
                    visited[neighbour] = true;
                }

                temp = temp->next;
            }
        }
    }

    void dfsUtil(int src, bool visited[])
    {
        visited[src] = true;
        cout << src << " ";

        Node *temp = adjList[src].head;
        while (temp != NULL)
        {
            int neigh = temp->data;
            if (!visited[neigh])
            {
                dfsUtil(neigh, visited);
            }
            temp = temp->next;
        }
    }

    void dfs(int src)
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }

        cout << "DFS Traversal : ";
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfsUtil(i, visited);
            }
        }
        delete[] visited;
        cout << endl;
    }

    bool isCycleDFS(int src, bool visited[], bool recStack[])
    {
        visited[src] = true;
        recStack[src] = true;

        Node *temp = adjList[src].head;
        while (temp != NULL)
        {
            int neighbour = temp->data;
            if (!visited[neighbour])
            {
                if (isCycleDFS(neighbour, visited, recStack))
                {
                    return true;
                }
            }
            else if (recStack[neighbour])
            {
                return true;
            }

            temp = temp->next;
        }

        recStack[src] = false;
        return false;
    }

    bool hasCycleDFS()
    {
        bool *visited = new bool[V]();
        bool *recStack = new bool[V]();

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && adjList[i].head != NULL)
            {
                if (isCycleDFS(i, visited, recStack))
                {
                    delete[] recStack;
                    delete[] visited;
                    return true;
                }
            }
        }
        delete[] visited;
        return false;
    }

    void topoSort(bool visited[], int src, Stack &s)
    {
        visited[src] = true;
        Node *temp = adjList[src].head;
        while (temp != NULL)
        {
            int neighbour = temp->data;
            if (!visited[neighbour])
            {
                topoSort(visited, neighbour, s);
            }
            temp = temp->next;
        }

        s.push(src);
    }

    void callTopoSort()
    {
        if (hasCycleDFS())
        {
            cout << "Cycle detected! Topological sorting not possible.\n";
            return;
        }
        else
        {

            bool *visited = new bool[V]();
            Stack s;

            for (int i = 0; i < V; i++)
            {
                if (!visited[i] && adjList[i].head)
                {
                    topoSort(visited, i, s);
                }
            }

            cout << "Topological Sort : ";
            while (!s.isEmpty())
            {
                cout << s.peek() << " ";
                s.pop();
            }
            delete[] visited;
            cout << endl;
        }
    }

    bool hasEdge(int u, int v)
    {
        if (u >= V)
        {
            cout << "Invalid vertex" << endl;
            return false;
        }

        Node *temp = adjList[u].head;
        while (temp != NULL)
        {
            if (temp->data == v)
            {
                return true;
            }

            temp = temp->next;
        }

        return false;
    }

    void display()
    {
        // Adjacency Matrix Printing
        cout << "Adjacency Matrix" << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << adjMat[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        // Adjacency List printing
        cout << "Adjacency List" << endl;
        for (int i = 0; i < V; i++)
        {
            Node *temp = adjList[i].head;
            if (temp == NULL)
                continue;
            cout << i << " -> ";
            adjList[i].display();
            cout << endl;
        }
    }
};

int main()
{
    int Vertices, Edges;
    cout << "Enter Number of Vertices and Edges : ";
    cin >> Vertices >> Edges;
    Graph g(Vertices);

    for (int i = 0; i < Edges; i++)
    {
        int u, v;
        cout << "Enter u and v : ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    // g.display();
    cout << "BFS Traversal : ";
    g.bfs(0);
    cout << endl;

    cout << "DFS Traversal : ";
    bool *visited = new bool[Vertices]();
    g.dfs(0);
    cout << endl;

    cout << g.hasCycleDFS() << endl;

    g.callTopoSort();

    int u, v;
    cout << "Enter the vertices for whic you want to check : " << endl;
    cin >> u, v;
    if (g.hasEdge(u, v))
    {
        cout << "Edge Exist" << endl;
    }
    else
    {
        cout << "Edge does not Exist" << endl;
    }
    return 0;
}

// vertices={1,2,3,4,5,6}
// edges={{1,2},{1,4},{1,6},{3,2},{3,4},{3,6},{5,2},{5,4},{5,6}}
// vertices={a,b,c,d,e,f}
// edges={{a,d},{a,e},{a,f},{b,d},{b,e},{b,f},{c,d},{c,e},{c,f}}