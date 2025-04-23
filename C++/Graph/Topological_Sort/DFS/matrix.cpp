#include <iostream>
#include <fstream>
#include <climits>
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

    void topologicalSortUtil(int src, bool visited[], stack<int> &s)
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

        cout << "Topological Sort : ";
        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }

        cout << endl;
        delete[] visited;
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
    g->topologicalsort();
    return 0;
}