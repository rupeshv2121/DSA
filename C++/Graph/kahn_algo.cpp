#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
using namespace std;

class graph
{
public:
    unordered_map<int, list<int>> adj;
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void topoSort()
    {
        // calculate indegree
        vector<int> inDegree(adj.size());
        for (auto i : adj)
        {
            for (auto j : i.second)
            {
                inDegree[j]++;
            }
        }

        // push 0 indegree nodes to queue
        queue<int> q;
        for (int i = 0; i < adj.size(); i++)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
            }
        }

        unordered_map<int, bool> visited;
        while (!q.empty())
        {
            int currNode = q.front();
            q.pop();

            cout << currNode << " ";

            for (auto i : adj[currNode])
            {
                inDegree[i]--;
                if (inDegree[i] == 0)
                {
                    q.push(i);
                }
            }
        }
    }

    void printGraph()
    {
        for (auto i : adj)
        {
            cout << i.first << " -> ";
            for (auto j : i.second)
            {
                cout << j << " ";
            }
            cout << endl;
        }

        cout << "END";
    }
};

int main()
{
    int node;
    cout << "Enter Number of Nodes: ";
    cin >> node;

    int edges;
    cout << "Enter Number of Edges : ";
    cin >> edges;

    graph g;

    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cout << "Enter Node data : ";
        cin >> u >> v;

        g.addEdge(u, v);
    }

    g.topoSort();
    g.printGraph();
    return 0;
}