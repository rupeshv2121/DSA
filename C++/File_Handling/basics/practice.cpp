#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
        adjMat[v][u] = wt;
    }

    void display()
    {
        cout << "Adjacency Matrix:" << endl;
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
    ifstream inputFile("practice.txt");
    if (!inputFile.is_open())
    {
        cerr << "File is not opened Successfully" << endl;
        return 1;
    }

    string line;
    int lineNumber = 1;
    int nov = 0;
    Graph *g = nullptr;

    while (getline(inputFile, line))
    {
        if (lineNumber == 1)
        {
            // Parse vertices: v={A,B,C,D}
            size_t start = line.find('{') + 1;
            size_t end = line.find('}');
            string vertices = line.substr(start, end - start);
            stringstream ss(vertices);
            string vertex;
            while (getline(ss, vertex, ','))
            {
                nov++;
            }
            g = new Graph(nov);
        }
        else if (lineNumber == 2)
        {
            // Parse edges: e={{A,B,2},{A,D,5},...}
            size_t start = line.find('{') + 1;
            size_t end = line.find_last_of('}');
            string edgeList = line.substr(start, end - start);
            stringstream ss(edgeList);
            string edge;

            while (getline(ss, edge, '}'))
            {
                size_t l = edge.find('{');
                if (l != string::npos)
                {
                    edge = edge.substr(l + 1); // skip '{'
                    stringstream edgeStream(edge);
                    string uStr, vStr, wtStr;
                    getline(edgeStream, uStr, ',');
                    getline(edgeStream, vStr, ',');
                    getline(edgeStream, wtStr, ',');

                    int u = uStr[0] - 'A';
                    int v = vStr[0] - 'A';
                    int wt = stoi(wtStr);

                    g->addEdge(u, v, wt);
                }
            }
        }

        lineNumber++;
    }

    inputFile.close();

    g->display();
    delete g;

    return 0;
}
