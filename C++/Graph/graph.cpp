#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
using namespace std;

class graph
{
public:
    unordered_map<int, list<int>> adj;

    void addEdge(int u, int v, bool direction)
    {
        // direc -> 0 for undirected
        // direc -> 1 for directed

        adj[u].push_back(v);
        // if (direction == 0)
        // {
        //     adj[v].push_back(u);
        // }
    }

    void bfs(int src)
    {
        unordered_map<int, bool> visited;
        queue<int> q;

        q.push(src);
        visited[src] = true;

        while (!q.empty())
        {
            int currNode = q.front();
            cout << currNode << " -> ";
            q.pop();

            for (auto neighbor : adj[currNode])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "END" << endl;
    }

    void dfs(int src, unordered_map<int, bool> &visited)
    {
        cout << src << " -> ";
        visited[src] = true;

        for (auto i : adj[src])
        {
            if (!visited[i])
            {
                dfs(i, visited);
            }
        }
    }

    bool isCycleBFS(int src, unordered_map<int, bool> &visited)
    {
        unordered_map<int, int> parent;
        visited[src] = true;
        parent[src] = -1;

        queue<int> q;
        q.push(src);

        while (!q.empty())
        {
            int currNode = q.front();
            q.pop();

            for (auto i : adj[currNode])
            {
                if (visited[i] == true && i != parent[currNode])
                {
                    return true;
                }
                else if (!visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                    parent[i] = currNode;
                }
            }
        }

        return false;
    }

    bool hasCycleBFS()
    {
        unordered_map<int, bool> visited;
        for (auto node : adj)
        {
            if (!visited[node.first])
            {
                if (isCycleBFS(node.first, visited))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCycleDFS(int src, unordered_map<int, bool> &visited, int parent)
    {
        visited[src] = true;

        for (auto i : adj[src])
        {
            if (!visited[i])
            {
                bool cycleDetected = isCycleDFS(i, visited, src);
                if (cycleDetected)
                {
                    return true;
                }
            }
            else if (i != parent)
            {
                return true;
            }
        }

        return false;
    }

    bool hasCycleDFS()
    {
        unordered_map<int, bool> visited;
        for (auto node : adj)
        {
            if (!visited[node.first])
            {
                if (isCycleDFS(node.first, visited, -1))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCycleDFS(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &recStack)
    {
        visited[node] = true;
        recStack[node] = true;

        for (auto neighbor : adj[node])
        {
            if (!visited[neighbor] && isCycleDFS(neighbor, visited, recStack))
                return true;
            else if (recStack[neighbor])
                return true;
        }

        recStack[node] = false;
        return false;
    }

    bool hasCycleDirected()
    {
        unordered_map<int, bool> visited;
        unordered_map<int, bool> recStack;

        for (auto node : adj)
        {
            if (!visited[node.first])
            {
                if (isCycleDFS(node.first, visited, recStack))
                    return true;
            }
        }
        return false;
    }

    void topoSort(unordered_map<int, bool> &visited, stack<int> &s, int src)
    {
        visited[src] = true;

        for (auto i : adj[src])
        {
            if (!visited[i])
            {
                topoSort(visited, s, i);
            }
        }

        s.push(src);
    }

    void callTopoSort()
    {
        if (hasCycleDirected())
        {
            cout << "Cycle detected! Topological sorting is not possible." << endl;
            return;
        }

        unordered_map<int, bool> visited;
        stack<int> s;
        for (auto i : adj)
        {
            if (!visited[i.first])
            {
                topoSort(visited, s, i.first);
            }
        }

        cout << "Topological Order: ";
        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    }

    void printAdjList()
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
    }
};

int main()
{
    int n;
    cout << "Enter number of nodes : ";
    cin >> n;

    cout << endl;

    int m;
    cout << "Enter number of edges : ";
    cin >> m;

    graph g;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cout << "Enter nodes : ";
        cin >> u >> v;

        // adding edges
        g.addEdge(u, v, 0);
    }

    unordered_map<int, bool> visited;

    // int startNode;
    // cout << "Enter the Starting Node : ";
    // cin >> startNode;
    // g.bfs(startNode);

    // // unordered_map<int, bool> vis;
    // cout << "Enter the starting Node : ";
    // cin >> startNode;
    // g.dfs(startNode, visited);
    // cout << "END" << endl;

    // cout << "is cycle present by BFS ? " << g.hasCycleBFS() << endl;
    // cout << "is cycle present by DFS ? " << g.hasCycleDFS() << endl;

    g.callTopoSort();

    // printing graph
    // g.printAdjList();

    return 0;
}