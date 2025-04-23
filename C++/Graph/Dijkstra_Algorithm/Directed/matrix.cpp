#include <iostream>
#include <fstream>
#include <climits>
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

    void dijkstra(int src)
    {
        int *dist = new int[V];
        bool *visited = new bool[V];

        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            dist[i] = INT_MAX / 2;
        }

        dist[src] = 0;

        for (int i = 0; i < V; i++)
        {
            int u = minDistance(dist, visited);

            visited[u] = true;
            for (int v = 0; v < V; v++)
            {
                if (!visited[v] && adjMat[u][v] && dist[u] + adjMat[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjMat[u][v];
                }
            }
        }

        for (int i = 0; i < V; i++)
        {
            cout << src << " -> " << i << " (" << dist[i] << ")" << endl;
        }
    }

    int minDistance(int dist[], bool visited[])
    {
        int min = INT_MAX, minIdx = -1;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && dist[i] < min)
            {
                minIdx = i;
                min = dist[i];
            }
        }

        return minIdx;
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
    g->dijkstra(0);
    return 0;
}