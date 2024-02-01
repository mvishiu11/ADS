#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum class EdgeType {
    TREE, FORWARD, BACK, CROSS
};

struct Edge {
    int from, to;
    EdgeType type;
};

void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& discoveryTime, vector<int>& finishingTime, vector<Edge>& edges, int& time) {
    visited[node] = true;
    discoveryTime[node] = ++time;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            edges.push_back({node, neighbor, EdgeType::TREE});
            dfs(neighbor, graph, visited, discoveryTime, finishingTime, edges, time);
        } else {
            if (discoveryTime[node] < discoveryTime[neighbor]) {
                // Node was discovered before neighbor but neighbor has not finished, this is a forward edge.
                edges.push_back({node, neighbor, EdgeType::FORWARD});
            } else if (finishingTime[neighbor] == 0) {
                // Neighbor was discovered and has not finished, so it's an ancestor of node, this is a back edge.
                edges.push_back({node, neighbor, EdgeType::BACK});
            } else {
                // Neighbor is neither descendant nor ancestor, so this is a cross edge.
                edges.push_back({node, neighbor, EdgeType::CROSS});
            }
        }
    }

    finishingTime[node] = ++time;
}

int main() {
    int z;
    cin >> z;
    while (z--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);
        vector<int> discoveryTime(n, 0), finishingTime(n, 0);
        vector<Edge> edges;
        
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            graph[x].push_back(y);
        }
        
        int time = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i, graph, visited, discoveryTime, finishingTime, edges, time);
            }
        }
        
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.from < b.from || (a.from == b.from && a.to < b.to);
        });

        for (const Edge& edge : edges) {
            cout << edge.from << " " <<edge.to;
            switch (edge.type) {
                case EdgeType::TREE: cout << " T"; break;
                case EdgeType::FORWARD: cout << " F"; break;
                case EdgeType::BACK: cout << " B"; break;
                case EdgeType::CROSS: cout << " C"; break;
            }
            cout << endl;
        }
    }
    return 0;
}