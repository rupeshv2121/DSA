#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

const int N = 100;
int parent[N];
int sz[N];

class Node
{
public:
    int u, v, wt;
    Node() {}
    Node(int u, int v, int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
};

Node edges[N * N];
int edgesCount = 0;

class Graph
{
    int V;
    int **adjMat;

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
    }

    void addEdge(int u, int v, int wt)
    {
        adjMat[u][v] = wt;
    }

    void make_set(int v)
    {
        parent[v] = v;
        sz[v] = 1;
    }

    int find_set(int v)
    {
        if (v == parent[v])
        {
            return v;
        }

        return parent[v] = find_set(parent[v]);
    }

    void union_set(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);

        if (a != b)
        {
            if (sz[a] > sz[b])
            {
                swap(a, b);
            }
            parent[b] = a;
            sz[a] += sz[b];
        }
    }

    void sortEdges()
    {
        for (int i = 0; i < edgesCount - 1; i++)
        {
            for (int j = 0; j < edgesCount - i - 1; j++)
            {
                if (edges[j].wt > edges[j + 1].wt)
                {
                    Node temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }

    void kruskal()
    {
        int mstCost = 0;

        for (int i = 0; i < V; i++)
        {
            make_set(i);
        }

        sortEdges();

        for (int i = 0; i < edgesCount; i++)
        {
            int u = edges[i].u;
            int v = edges[i].v;
            int wt = edges[i].wt;

            if (find_set(u) != find_set(v))
            {
                union_set(u, v);
                cout << u << " -> " << v << " (" << wt << ")" << endl;
                mstCost += wt;
            }
        }

        cout << "Cost of MST : " << mstCost << endl;
    }

    void display()
    {
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
    ifstream inputFile("input.txt");
    if (inputFile.is_open())
    {
        cout << "File open successfully" << endl;
    }

    Graph *g = nullptr;
    string line;
    int lineNumber = 1;
    int nov = 0;

    while (getline(inputFile, line))
    {
        if (lineNumber == 1)
        {
            for (int i = 3; i < line.length() - 1; i++)
            {
                if (line[i] != ',')
                {
                    nov++;
                }
            }

            cout << "Vertices : " << nov << endl;
            g = new Graph(nov);
        }
        else if (lineNumber == 2)
        {
            for (int i = 3; i < line.length() - 1; i++)
            {
                if (line[i] == '{' && i + 6 < line.length())
                {
                    int u = line[i + 1] - '0';
                    int v = line[i + 3] - '0';

                    int wt;
                    if (line[i + 5] == '-')
                    {
                        wt = -(line[i + 6] - '0');
                    }
                    else
                    {
                        wt = line[i + 5] - '0';
                    }

                    g->addEdge(u, v, wt);
                    edges[edgesCount++] = Node(u, v, wt);
                }
            }
        }
        lineNumber++;
    }

    g->display();
    g->kruskal();
    return 0;
}