#include <iostream>
#include <fstream>
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
int edgeCount = 0;
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

        cout << "Graph initialised Successfully" << endl;
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

    int union_set(int a, int b)
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
        for (int i = 0; i < edgeCount - 1; i++)
        {
            for (int j = 0; j < edgeCount - i - 1; j++)
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

    int kruskal(int V)
    {
        int mst_weight = 0;

        for (int i = 0; i < V; i++)
        {
            make_set(i);
        }

        sortEdges();

        for (int i = 0; i < edgeCount; i++)
        {
            int u = edges[i].u;
            int v = edges[i].v;
            int wt = edges[i].wt;

            if (find_set(u) != find_set(v))
            {
                union_set(u, v);
                mst_weight += wt;
                cout << "Edge " << u << " - " << v << " included with weight " << wt << endl;
            }
        }

        return mst_weight;
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

    int lineNumber = 1;
    string line;
    Graph *g = nullptr;
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
                        cout << wt << " ";
                    }
                    else
                    {
                        wt = line[i + 5] - '0';
                    }

                    g->addEdge(u, v, wt);
                    edges[edgeCount++] = Node(u, v, wt);
                }
            }
        }
        lineNumber++;
    }

    g->display();
    int mst = g->kruskal(nov);
    cout << "Total weight of MST = " << mst << endl;

    return 0;
}