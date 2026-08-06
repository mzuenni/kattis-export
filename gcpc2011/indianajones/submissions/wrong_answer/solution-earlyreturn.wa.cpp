
#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;
using ll = long long;

void print(vector<int>&v){
    for (auto x:v) cout << x << " ";
    cout << endl;
}

inline int fastscan()
{
    bool negative = false;
    int c;
    int number = 0;
    c = getchar_unlocked();
    if (c == '-')
    {
        negative = true;
        c = getchar_unlocked();
    }
    for (; (c > 47 && c < 58); c = getchar_unlocked())
        number = number * 10 + c - 48;
    if (negative) number *= -1;
    return number;
}

class Graph {
    // No. of vertices'
    int V;

    // Pointer to an array containing
    // adjacency listsList
    list<int>* adj;

public:
    // Constructor
    Graph(int V);

    // Function to add an edge to graph
    void addEdge(int u, int v);

    // prints a Topological Sort of
    // the complete graph
    void topologicalSort();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

// The function to do
// Topological Sort.
void Graph::topologicalSort()
{
    // Create a vector to store
    // indegrees of all
    // vertices. Initialize all
    // indegrees as 0.
    vector<int> in_degree(V, 0);

    // Traverse adjacency lists
    // to fill indegrees of
    // vertices.  This step
    // takes O(V+E) time
    for (int u = 0; u < V; u++) {
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)
            in_degree[*itr]++;
    }

    // Create an queue and enqueue
    // all vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    // Initialize count of visited vertices
    int cnt = 0;

    // Create a vector to store
    // result (A topological
    // ordering of the vertices)
    vector<int> top_order;

    // One by one dequeue vertices
    // from queue and enqueue
    // adjacents if indegree of
    // adjacent becomes 0
    while (!q.empty()) {
        // Extract front of queue
        // (or perform dequeue)
        // and add it to topological order
        if (q.size()>1){
            cout << "missing hints" << endl;
            return;
        }
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        // Iterate through all its
        // neighbouring nodes
        // of dequeued node u and
        // decrease their in-degree
        // by 1
        list<int>::iterator itr;
        for (itr = adj[u].begin();
             itr != adj[u].end(); itr++)

            // If in-degree becomes zero,
            // add it to queue
            if (--in_degree[*itr] == 0)
                q.push(*itr);

        cnt++;
    }

    // Check if there was a cycle
    if (cnt != V) {
        cout << "recheck hints" << endl;
        return;
    }

    // Print topological order
    for (int i = 0; i < top_order.size(); i++)
        cout << top_order[i]+1 << " ";
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    int t; //number of testscases
    t = fastscan();
    rep(i, t){
        int n; //number of switches
        int h; //number of hints
        n = fastscan();
        h = fastscan();

        Graph g(n);
        rep(_, h){
            int a, b;
            a = fastscan();
            b = fastscan();
            g.addEdge(a-1, b-1);
        }

        g.topologicalSort();
    }

    return 0;

}