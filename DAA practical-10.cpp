#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

bool compare(Edge a, Edge b) {
    return a.w < b.w;
}

int findParent(vector<int>& parent, int x) {
    if (parent[x] != x)
        parent[x] = findParent(parent, parent[x]);
    return parent[x];
}

int main() {
    int n, e;
    cout << "Enter vertices and edges: ";
    cin >> n >> e;

    vector<Edge> edges(e);
    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < e; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n);
    for (int i = 0; i < n; i++)
        parent[i] = i;

    int total = 0, count = 0;
    cout << "MST edges:\n";

    for (Edge edge : edges) {
        int a = findParent(parent, edge.u);
        int b = findParent(parent, edge.v);

        if (a != b) {
            cout << edge.u << " - " << edge.v
                 << " : " << edge.w << endl;

            parent[a] = b;
            total += edge.w;
            count++;
        }

        if (count == n - 1)
            break;
    }

    if (count != n - 1)
        cout << "Graph is disconnected; MST does not exist.\n";
    else
        cout << "Total MST weight: " << total << endl;

    return 0;