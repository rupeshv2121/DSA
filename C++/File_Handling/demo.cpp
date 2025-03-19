#include <iostream>
#include <fstream>
#include <sstream>
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

    void display(ostream &fout)
    {
        Node *temp = head;
        while (temp != NULL)
        {
            fout << temp->data << " ";
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

    void transpose(ostream &fout)
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
        }

        fout << "Tranposed Matrix : " << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                fout << dupMat[i][j] << " ";
            }
            fout << endl;
        }
    }

    void display(ostream &fout)
    {
        for (int i = 0; i < V; i++)
        {
            fout << i << " -> ";
            adjList[i].display(fout);
            fout << endl;
        }

        // Adjacency Matrix
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                fout << adjMat[i][j] << " ";
            }
            fout << endl;
        }
    }
};

int main()
{
    int Vertices;
    cout << "Enter Number of Vertices : ";
    cin >> Vertices;
    Graph g(Vertices);

    ifstream fin;
    fin.open("inp.txt");

    ofstream fout;
    fout.open("out.txt");

    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "ADD")
        {
            int u, v;
            ss >> u >> v;
            g.addEdge(u, v);
        }

        if (command == "DISPLAY")
        {
            g.display(fout);
        }

        if (command == "TRANSPOSE")
        {
            g.transpose(fout);
        }
    }

    fin.close();
    fout.close();
    return 0;
}