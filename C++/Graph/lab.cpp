#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>
#include <string>
#include <stack>
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
        // adjMat[v][u] = wt;
    }

    void dfsUtil(bool visited[], int src)
    {
        visited[src] = true;
        cout << src << " ";
        for (int i = 0; i < V; i++)
        {
            if (adjMat[src][i] && !visited[i])
            {
                dfsUtil(visited, i);
            }
        }
    }

    void dfs(int src)
    {
        bool *visited = new bool[V]{0};
        cout << "DFS Traversal : ";
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfsUtil(visited, i);
            }
        }
        cout << endl;
        delete[] visited;
    }

    void bfs(int src)
    {
        bool *visited = new bool[V]{0};
        queue<int> q;
        q.push(src);
        visited[src] = true;

        cout << "BFS Traversal : ";
        while (!q.empty())
        {
            int curr = q.front();
            q.pop();
            cout << curr << " ";

            for (int i = 0; i < V; i++)
            {
                if (adjMat[curr][i] && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << endl;
    }

    int minDistance(int dist[], bool visited[])
    {
        int min = INT_MAX, minIdx;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && dist[v] < min)
            {
                minIdx = v;
                min = dist[v];
            }
        }

        return minIdx;
    }

    void dijkstra(int src)
    {
        int *dist = new int[V]{INT_MAX};
        bool *visited = new bool[V]{false};

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
            for (int v = 0; v < V; v++)
            {
                if (adjMat[u][v] && !visited[v] && dist[u] != INT_MAX && dist[u] + adjMat[u][v] < dist[v])
                {
                    dist[v] = dist[u] + adjMat[u][v];
                }
            }
        }

        cout << "Dijkstra : " << endl;
        for (int i = 0; i < V; i++)
        {
            cout << src << " -> " << i << "(" << dist[i] << ")" << endl;
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

        for (int i = 0; i < V; i++)
        {
            if (dist[i][i] < 0)
            {
                cout << "Negative cycle detected" << endl;
                return;
            }
        }

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

    void prim(int src)
    {
        bool *mstSet = new bool[V];
        int *dist = new int[V];
        int *parent = new int[V];
        int finalCost = 0;

        for (int i = 0; i < V; i++)
        {
            mstSet[i] = false;
            dist[i] = INT_MAX;
        }

        dist[src] = 0;
        parent[src] = -1;

        for (int i = 0; i < V - 1; i++)
        {
            int u = minDistance(dist, mstSet);

            mstSet[u] = true;
            for (int v = 0; v < V; v++)
            {
                if (!mstSet[v] && adjMat[u][v] && adjMat[u][v] < dist[v])
                {
                    parent[v] = u;
                    dist[v] = adjMat[u][v];
                }
            }
        }

        cout << "Prim Algorithm : " << endl;
        for (int i = 1; i < V; i++)
        {
            finalCost += dist[i];
            cout << parent[i] << " -> " << i << " : " << adjMat[i][parent[i]] << endl;
        }
        cout << "Cost of MST : " << finalCost << endl;
    }

    int find(int parent[], int i)
    {
        if (parent[i] == -1)
        {
            return i;
        }

        return find(parent, parent[i]);
    }

    void Union(int parent[], int x, int y)
    {
        int parX = find(parent, x);
        int parY = find(parent, y);

        if (parX != parY)
        {
            parent[parX] = parY;
        }
    }

    bool hasPath(int src, int dest, bool visited[])
    {
        if (src == dest)
        {
            return true;
        }

        visited[src] = true;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && adjMat[src][i] && hasPath(i, dest, visited))
            {
                return true;
            }
        }

        return false;
    }

    bool cycleDetect(int src, bool visited[], int par)
    {
        visited[src] = true;

        for (int i = 0; i < V; i++)
        {
            if (adjMat[src][i])
            {
                if (!visited[i])
                {
                    if (cycleDetect(i, visited, src))
                    {
                        return true;
                    }
                }
                else if (visited[i] && i != par && adjMat[src][i])
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool hasCycle()
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (cycleDetect(i, visited, -1))
                {
                    delete[] visited;
                    return true;
                }
            }
        }

        delete[] visited;
        return false;
    }

    bool cycleDetectDirected(int src, bool visited[], bool recStack[])
    {

        visited[src] = true;
        recStack[src] = true;

        for (int i = 0; i < V; i++)
        {
            if (adjMat[src][i])
            {
                if (!visited[i] && cycleDetectDirected(i, visited, recStack))
                    return true;
                else if (recStack[i])
                    return true;
            }
        }

        recStack[src] = false;
        return false;
    }

    bool hasCycleDirected()
    {
        bool *visited = new bool[V]{false};
        bool *recStack = new bool[V]{false};

        for (int i = 0; i < V; i++)
        {
            if (cycleDetectDirected(i, visited, recStack))
            {
                delete[] visited;
                delete[] recStack;
                return true;
            }
        }

        delete[] visited;
        delete[] recStack;
        return false;
    }

    void topologicalSortUtil(int src, bool visited[], stack<int> s)
    {
        visited[src] = true;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && adjMat[src][i])
            {
                topologicalSortUtil(i, visited, s);
            }
        }
        s.push(src);
    }

    void topologicalsort()
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }

        stack<int> s;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                topologicalSortUtil(i, visited, s);
            }
        }

        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }

        cout << endl;
        delete[] visited;
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
        cout << "File Open Successfully" << endl;
    }
    else
    {
        cout << "File doesn't Open" << endl;
    }

    Graph *g = nullptr;

    string line;
    int nov = 0;
    int lineNumber = 1;
    while (getline(inputFile, line))
    {
        if (lineNumber == 1)
        {
            for (int i = 10; i < line.length() - 1; i += 1)
            {
                if (line[i] != ',')
                {
                    nov++;
                }
            }
            g = new Graph(nov);
        }
        else if (lineNumber == 2)
        {
            for (int i = 7; i < line.length() - 1; i++)
            {
                if (line[i] == '{' && line[i + 2] == ',' && line[i + 4] == ',' && line[i + 6] == '}')
                {
                    int u = line[i + 1] - '0';
                    int v = line[i + 3] - '0';
                    int wt = line[i + 5] - '0';

                    g->addEdge(u, v, wt);
                }
            }
        }

        lineNumber++;
    }

    g->display();
    g->dfs(0);
    g->bfs(0);
    g->dijkstra(0);
    g->floydWarshall();
    g->prim(0);

    bool visited[nov], visited2[nov];
    for (int i = 0; i < nov; i++)
    {
        visited[i] = false;
        visited2[i] = false;
    }
    cout << g->hasPath(0, 5, visited) << endl;
    cout << g->hasCycleDirected() << endl;
    g->topologicalsort();
    return 0;
}

// int extractNumber(const string& s, int& pos)
// {
//     int num = 0;
//     int sign = 1;

//     // Handle negative numbers
//     if (pos < s.length() && s[pos] == '-')
//     {
//         sign = -1;
//         pos++;
//     }

//     // Extract digits
//     while (pos < s.length() && isdigit(s[pos]))
//     {
//         num = num * 10 + (s[pos] - '0');
//         pos++;
//     }

//     return sign * num;
// }