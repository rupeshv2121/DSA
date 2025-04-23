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

    void flyodWarshall()
    {
        int dist[V][V];
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (i == j)
                {
                    dist[i][j] = 0;
                }
                else if (adjMat[i][j] != 0)
                {
                    dist[i][j] = adjMat[i][j];
                }
                else
                {
                    dist[i][j] = INT_MAX / 2;
                }
            }
        }
        for (int k = 0; k < V; k++)
        {
            for (int i = 0; i < V; i++)
            {
                for (int j = 0; j < V; j++)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        // Negative Cycle Detection
        for (int i = 0; i < V; i++)
        {
            if (dist[i][i] < 0)
            {
                cout << "Negative Cycle Detected" << endl;
                return;
            }
        }

        cout << "Floyd Warshall Output " << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] == INT_MAX / 2)
                {
                    cout << "INF ";
                }
                else
                {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
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
    g->flyodWarshall();
    return 0;
}