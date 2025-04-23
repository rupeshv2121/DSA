#include <iostream>
#include <climits>
#include <fstream>
using namespace std;

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

    void bellmanFord(int src)
    {
        int *dist = new int[V];

        for (int i = 0; i < V; i++)
        {

            dist[i] = INT_MAX / 2;
        }

        dist[src] = 0;

        for (int i = 0; i < V - 1; i++)
        {
            for (int u = 0; u < V; u++)
            {
                for (int v = 0; v < V; v++)
                {
                    if (adjMat[u][v] && dist[u] != INT_MAX && dist[u] + adjMat[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + adjMat[u][v];
                    }
                }
            }
        }

        bool hasNegativeCycle = false;
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (adjMat[u][v] && dist[u] != INT_MAX && dist[u] + adjMat[u][v] < dist[v])
                {
                    hasNegativeCycle = true;
                    break;
                }
            }
        }

        if (hasNegativeCycle)
        {
            cout << "Negative Cycle Detected" << endl;
        }
        else
        {
            for (int i = 0; i < V; i++)
            {
                cout << src << " -> " << i << " ( ";
                if (dist[i] == INT_MAX)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << dist[i] << " ";
                }
                cout << ")" << endl;
            }
        }
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
                }
            }
        }
        lineNumber++;
    }

    g->display();
    g->bellmanFord(0);
    return 0;
}