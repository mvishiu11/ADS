#include <iostream>
#include <vector>
#include <limits>
#include <climits>

using namespace std;

#define INF INT_MAX

struct Edge {
    int src, dest, weight;
};

void printSolution(const vector<int>& dist, int n) {
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) {
            cout << 'I' << ' ';
        } else {
            cout << dist[i] << ' ';
        }
    }
    cout << endl;
}

void BellmanFord(int n, int m, const vector<Edge>& edges) {
    vector<int> dist(n, INF);
    dist[0] = 0;

    // Relax all edges |V| - 1 times.
    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles.
    for (int i = 0; i < m; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            cout << "NC" << endl;
            return;
        }
    }

    printSolution(dist, n);
}

int main() {
    int z, n, m;
    cin >> z;

    while (z--) {
        cin >> n >> m;
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
        }
        BellmanFord(n, m, edges);
    }

    return 0;
}