#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(vector<vector<pii>>& graph, int n) {
    priority_queue<pii, vector<pii>, greater<pii>> minHeap;
    vector<int> dist(n, INT_MAX);

    dist[0] = 0;
    minHeap.push({0, 0});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                minHeap.push({dist[v], v});
            }
        }
    }

    if (dist[n - 1] == INT_MAX)
        cout << -1 << endl;
    else
        cout << dist[n - 1] << endl;
}

int main() {
    int z, n, m, u, v, w;
    cin >> z;

    while (z--) {
        cin >> n >> m;
        vector<vector<pii>> graph(n);

        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
        }

        dijkstra(graph, n);
    }

    return 0;
}