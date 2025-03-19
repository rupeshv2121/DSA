#include <iostream>
using namespace std;

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
    Node *head = NULL;
    Node *tail = NULL;

public:
    void addNode(int data)
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
    int adjMat[10][10];
    int dupMat[10][10];
    LinkedList adjList[10];

public:
    Graph(int V)
    {
        this->V = V;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                adjMat[i][j] = 0;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                dupMat[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v)
    {
        adjList[u].addNode(v);
        adjMat[u][v] = 1;
    }

    void tranpose()
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (adjMat[i][j] == 1)
                {
                    dupMat[j][i] = 1;
                }
            }
            cout << endl;
        }

        cout << "Tranposed Matrix : " << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << dupMat[i][j] << " ";
            }
            cout << endl;
        }
    }

    void display()
    {
        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";
            adjList[i].display();
            cout << endl;
        }

        // Adjacency Matrix
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << adjMat[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    int Vertices;
    cout << "Enter Number of Vertices : ";
    cin >> Vertices;
    Graph g(Vertices);

    cout << "1. Create Graph by Giving Vertices : " << endl;
    cout << "2. Display Graph : " << endl;
    cout << "3. Tranpose Of Graph : " << endl;
    cout << "4. Exit !" << endl;

    while (true)
    {
        int choice;
        cout << "Enter Choice : ";
        cin >> choice;

        if (choice == 1)
        {
            bool var = true;
            while (var)
            {
                int u, v;
                cout << "Enter Nodes : ";
                cin >> u >> v;
                g.addEdge(u, v);

                int x;
                cout << "Do you want to add More Nodes : ";
                cin >> x;
                if (x == -1)
                {
                    break;
                }
            }
        }

        if (choice == 2)
        {
            g.display();
        }

        if (choice == 3)
        {
            g.tranpose();
        }

        if (choice == 4)
        {
            break;
        }
    }
    return 0;
}