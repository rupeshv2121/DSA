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

    bool isBipartite()
    {
        bool *visited = new bool[V]{false};
        int *color = new int[V];
        for (int i = 0; i < V; i++)
        {
            color[i] = -1;
        }

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (!isBipartiteUtil(i, visited, color, 0))
                {
                    delete[] visited;
                    delete[] color;
                    return false;
                }
            }
        }

        delete[] visited;
        delete[] color;
        return true;
    }

    bool isBipartiteUtil(int src, bool visited[], int color[], int currColor)
    {
        visited[src] = true;
        color[src] = currColor;

        for (int i = 0; i < V; i++)
        {
            if (adjMat[src][i] != 0) // only check neighbors
            {
                if (color[i] == -1)
                {
                    if (!isBipartiteUtil(i, visited, color, 1 - currColor))
                    {
                        return false;
                    }
                }
                else
                {
                    if (color[i] == color[src])
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void
    display()
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
    if (g->isBipartite())
    {
        cout << "Bipartite Graph" << endl;
    }
    else
    {
        cout << "Not a Bipartite Graph" << endl;
    }
    return 0;
}