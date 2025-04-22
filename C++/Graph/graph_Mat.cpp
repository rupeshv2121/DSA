#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Graph
{
    int V;
    int **adjMat;
    // int **adjMat2;

public:
    Graph(int V)
    {
        this->V = V;
        adjMat = new int *[V];
        // adjMat2 = new int *[V];

        for (int i = 0; i < V; i++)
        {
            adjMat[i] = new int[V];
            // adjMat2[i] = new int[V];
            for (int j = 0; j < V; j++)
            {
                adjMat[i][j] = 0;
                // adjMat2[i][j] = 0;
            }
        }
    }

    void addEdge(int u, int v, int wt)
    {
        adjMat[u][v] = wt;
        // adjMat[v][u] = wt;
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

    int minDistance(int dist[], bool visited[])
    {
        int min = INT_MAX;
        int minIdx;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && dist[i] <= min)
            {
                min = dist[i];
                minIdx = i;
            }
        }

        return minIdx;
    }

    void dijstra(int src)
    {
        int *dist = new int[V]{0};
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MAX;
            visited[i] = false;
        }

        dist[src] = 0;

        for (int i = 0; i < V - 1; i++)
        {
            int u = minDistance(dist, visited);

            visited[u] = true;

            for (int j = 0; j < V; j++)
            {
                if (!visited[j] && adjMat[u][j] && dist[u] != INT_MAX && dist[u] + adjMat[u][j] < dist[j])
                {
                    dist[j] = dist[u] + adjMat[u][j];
                }
            }
        }

        for (int i = 0; i < V; i++)
        {
            cout << src << " -> " << i << "(" << dist[i] << ")" << endl;
        }
    }

    void bellmanFord(int src)
    {
        int *dist = new int[V];
        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MAX;
        }
        dist[src] = 0;

        for (int i = 1; i <= V - 1; i++)
        {
            for (int u = 0; u < V; u++)
            {
                for (int v = 0; v < V; v++)
                {
                    if (adjMat[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adjMat[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + adjMat[u][v];
                    }
                }
            }
        }

        // Check for negative-weight cycles
        bool hasNegativeCycle = false;
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (adjMat[u][v] != 0 && dist[u] != INT_MAX && dist[u] + adjMat[u][v] < dist[v])
                {
                    cout << "Negative cycle" << endl;
                    hasNegativeCycle = true;
                    break;
                }
            }

            cout << endl;
            if (hasNegativeCycle)
                break;
        }

        if (hasNegativeCycle)
        {
            cout << "Graph contains a negative weight cycle!" << endl;
        }
        else
        {
            cout << "Bellman-Ford shortest distances from source " << src << ":" << endl;
            for (int i = 0; i < V; i++)
            {
                cout << src << " -> " << i << " (";
                if (dist[i] == INT_MAX)
                    cout << "INF";
                else
                    cout << dist[i];
                cout << ")" << endl;
            }
        }
    }

    void floydWarshall()
    {
        int dist[V][V];
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (i == j)
                    dist[i][j] = 0;
                else if (adjMat[i][j] != 0)
                    dist[i][j] = adjMat[i][j];
                else
                    dist[i][j] = INT_MAX / 2; // avoid overflow when adding
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

        // negative cycle detection
        for (int i = 0; i < V; i++)
        {
            if (dist[i][i] < 0)
            {
                cout << "Negative Cycle Detected" << endl;
                return;
            }
        }

        cout << "Floyd's Warshall : " << endl;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] == INT_MAX / 2)
                {
                    cout << "I ";
                }
                else
                {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    int minDist(int dist[], bool mstSet[])
    {
        int min = INT_MAX;
        int minIdx;

        for (int i = 0; i < V; i++)
        {
            if (!mstSet[i] && dist[i] < min)
            {
                min = dist[i];
                minIdx = i;
            }
        }

        return minIdx;
    }

    void primAlgo(int src)
    {
        int *parent = new int[V];
        int *dist = new int[V];
        bool *mstSet = new bool[V];

        for (int i = 0; i < V; i++)
        {
            mstSet[i] = false;
            dist[i] = INT_MAX;
        }

        dist[src] = 0;
        parent[src] = -1;

        for (int i = 0; i < V - 1; i++)
        {
            int u = minDist(dist, mstSet);
            mstSet[u] = true;

            for (int j = 0; j < V; j++)
            {
                if (!mstSet[j] && adjMat[u][j] && adjMat[u][j] < dist[j])
                {
                    parent[j] = u;
                    dist[j] = adjMat[u][j];
                }
            }
        }

        cout << "Edges in MST:" << endl;
        for (int i = 1; i < V; i++)
        {
            cout << parent[i] << " -> " << i << " : " << adjMat[i][parent[i]] << endl;
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

    Graph *g = nullptr, *g2 = nullptr;
    string line;

    int vertices1, edges1 = 0;
    int vertices2, edges2 = 0;
    int lineNumber = 1;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string name;
        if (lineNumber == 1)
        {
            int count = 0;
            getline(ss, name, '=');
            for (int i = 10; i < line.length() - 1; i++)
            {
                if (line[i] != ',')
                {
                    count++;
                }
            }
            vertices1 = count;
            g = new Graph(vertices1);
        }
        else if (lineNumber == 2)
        {
            getline(ss, name, '=');
            for (int i = 7; i < line.length() - 1; i++)
            {
                if (line[i] == '{' && line[i + 6] == '}' && line[i + 2] == ',' && line[i + 4] == ',')
                {
                    edges1++;
                    int u = line[i + 1] - '0'; // Numeric vertex for Graph 1
                    int v = line[i + 3] - '0'; // Numeric vertex for Graph 1
                    int wt = line[i + 5] - '0';

                    g->addEdge(u, v, wt);
                }
            }
        }
        // else if (lineNumber == 3)
        // {
        //     int count = 0;
        //     getline(ss, name, '=');
        //     for (int i = 10; i < line.length() - 1; i++)
        //     {
        //         if (line[i] != ',')
        //         {
        //             count++;
        //         }
        //     }
        //     vertices2 = count;
        //     g2 = new Graph(vertices2);
        // }
        // else
        // {
        //     getline(ss, name, '=');
        //     for (int i = 7; i < line.length() - 1; i++)
        //     {
        //         if (line[i] == '{' && line[i + 4] == '}' && line[i + 2] == ',')
        //         {
        //             edges2++;
        //             int u = line[i + 1] - 'a'; // Alphabetic vertex for Graph 2
        //             int v = line[i + 3] - 'a'; // Alphabetic vertex for Graph 2

        //             g2->addEdge2(u, v);
        //         }
        //     }
        // }
        lineNumber++;
    }

    cout << "Graph 1" << endl;
    g->display();

    cout << endl
         << "Vertices 1 = " << vertices1 << " , " << "Edges 1 = " << edges1;
    cout << endl;

    g->dijstra(0);
    g->bellmanFord(0);
    g->floydWarshall();
    g->primAlgo(0);

    // cout << "Graph 2" << endl;
    // g2->display2();
    // cout << endl
    //      << "Vertices 2 = " << vertices2 << " , " << "Edges 2 = " << edges2;

    // if (g->isIsomorphic(vertices1, edges1, vertices2, edges2))
    //     cout << "\nGraphs are isomorphic!" << endl;
    // else
    //     cout << "\nGraphs are NOT isomorphic!" << endl;

    return 0;
}
