#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSets {
public:
    vector<int> parent, rank;

    DisjointSets(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
        }
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
    }
};

struct Edge {
    int src, dest, weight;
};

bool compareWeight(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}

int kruskalMST(vector<Edge> &edges, int V) {
    sort(edges.begin(), edges.end(), compareWeight);

    DisjointSets ds(V);

    int mst_weight = 0;
    for (Edge &edge : edges) {
        int set_u = ds.find(edge.src);
        int set_v = ds.find(edge.dest);

        if (set_u != set_v) {
            mst_weight += edge.weight;
            ds.merge(set_u, set_v);
        }
    }

    return mst_weight;
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;
        vector<Edge> edges(m);

        for (int i = 0; i < m; i++) {
            cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
        }

        int mst_weight = kruskalMST(edges, n);

        // Check if all vertices are included in MST
        DisjointSets ds(n);
        for (Edge &edge : edges) {
            ds.merge(edge.src, edge.dest);
        }
        bool isConnected = true;
        int root = ds.find(0);
        for (int i = 1; i < n; i++) {
            if (ds.find(i) != root) {
                isConnected = false;
                break;
            }
        }

        if (isConnected) {
            cout << mst_weight << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}