#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <climits>

void depthFirstSearch(const std::vector<std::vector<bool>>& graph, std::vector<bool>& visited, int current, auto action) {
    visited[current] = true;
    for (int i = 0; i < graph.size(); ++i) {
        if (i != current && graph[current][i] && !visited[i]) {
            depthFirstSearch(graph, visited, i, action);
        }
    }
    action(current);
}

std::vector<std::vector<bool>> transposeMatrix(const std::vector<std::vector<bool>>& matrix) {
    std::vector<std::vector<bool>> transposed(matrix[0].size(), std::vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

std::vector<std::vector<int>> findStronglyConnectedComponents(const std::vector<std::vector<bool>>& graph) {
    std::vector<bool> visited(graph.size(), false);
    std::stack<int> stack;
    std::vector<std::vector<int>> SCCs;

    for (int i = 0; i < graph.size(); ++i) {
        if (!visited[i]) {
            depthFirstSearch(graph, visited, i, [&stack](int node) { stack.push(node); });
        }
    }

    auto transposed = transposeMatrix(graph);
    std::fill(visited.begin(), visited.end(), false);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        if (!visited[current]) {
            std::vector<int> SCC;
            depthFirstSearch(transposed, visited, current, [&SCC](int node) { SCC.push_back(node); });
            if (!SCC.empty()) {
                std::sort(SCC.begin(), SCC.end());
                SCCs.push_back(SCC);
            }
        }
    }

    return SCCs;
}

bool isSink(const std::vector<int>& v, const std::vector<std::vector<bool>>& graph) {
    for (int i : v) {
        for (int j = 0; j < graph.size(); ++j) {
            if (j != i && graph[i][j] && std::find(v.begin(), v.end(), j) == v.end()) {
                return false;
            }
        }
    }
         return true;
    }

int main() {
    int z, n, m, x, y;
    std::cin >> z;
    for (int i = 0; i < z; i++) {
        std::cin >> n >> m;
        std::vector<std::vector<bool>> infection(n, std::vector<bool>(n, false));
        for (int j = 0; j < m; j++) {
            std::cin >> x >> y;
            infection[x][y] = true;
        }

        auto SCCs = findStronglyConnectedComponents(infection);
        int smallestSinkSize = INT_MAX;

        for (const auto& SCC : SCCs) {
            if (isSink(SCC, infection)) {
                smallestSinkSize = std::min(smallestSinkSize, static_cast<int>(SCC.size()));
            }
        }

        if (smallestSinkSize != INT_MAX) {
            std::cout << smallestSinkSize << '\n';
        }
    }
    return 0;
}