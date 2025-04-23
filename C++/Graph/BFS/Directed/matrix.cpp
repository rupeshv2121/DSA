#include <iostream>
#include <fstream>
#include <queue>
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

    void BFS(int src)
    {
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
        }

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
                if (!visited[i] && adjMat[curr][i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
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
                    // cout << nov << endl;
                    nov++;
                }
            }
            cout << "Vertices -> " << nov << endl;
            g = new Graph(nov);
        }
        else if (lineNumber == 2)
        {
            // cout << line << " ";
            for (int i = 3; i < line.length() - 1; i++)
            {
                if (line[i] == '{' && i + 6 < line.length())
                {
                    int u = line[i + 1] - '0';
                    // cout << u << endl;
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

                    // cout << u << " " << v << " " << wt;
                    g->addEdge(u, v, wt);
                }
            }
        }
        lineNumber++;
    }

    g->display();
    g->BFS(0); // 0 1 2 4 3 5
    return 0;
}