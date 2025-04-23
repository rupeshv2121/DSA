#include <iostream>
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
                // cout << adjMat[i][j] << " ";
            }
            // cout << endl;
        }
        cout << "Graph initialised successfully" << endl;
    }

    void addEdge(int u, int v, int wt)
    {
        adjMat[u][v] = wt;
        // cout << u << " " << v << " " << wt << endl;
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

    void display()
    {
        cout << "Graph" << endl;
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
    if (g->hasCycleDirected())
    {
        cout << "Cycle Detected" << endl;
    }
    else
    {
        cout << "Cycle not Detected" << endl;
    }
    return 0;
}