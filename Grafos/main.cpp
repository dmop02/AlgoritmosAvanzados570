// Alvaro Solano | 01643948
// Domingo Mora | A01783317
//Referencias: https://www.codecademy.com/article/binary-search-in-cpp
// https://www.programiz.com/dsa/graph-bfs
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
};

using Graph = vector<vector<Edge>>;

// Complejidad: O((V + E) * log(W))
int findMinimumBatteryRange(const Graph& graph, int s, int t) {
    int left = 0, right = INF, result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        
        vector<bool> visited(graph.size(), false);
        queue<int> q;
        q.push(s);
        visited[s] = true;

        bool reachable = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == t) {
                reachable = true;
                break;
            }

            for (const auto& edge : graph[u]) {
                if (!visited[edge.to] && edge.weight <= mid) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }

        if (reachable) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

// Complejidad: O(V + E)
bool isRouteFeasible(const Graph& graph, int s, int t, int L) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) {
            return true;
        }

        for (const auto& edge : graph[u]) {
            if (!visited[edge.to] && edge.weight <= L) {
                visited[edge.to] = true;
                q.push(edge.to);
            }
        }
    }

    return false;
}

int main() {
    int n, m;
    cout << "Enter the number of cities (vertices) and roads (edges): ";
    cin >> n >> m;

    Graph graph(n);

    cout << "Enter the roads (u, v, weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int s, t;
    cout << "Enter the source city (s) and destination city (t): ";
    cin >> s >> t;

    // Complejidad: O((V + E) * log(W))
    int minBatteryRange = findMinimumBatteryRange(graph, s, t);
    if (minBatteryRange != -1) {
        cout << "Minimum battery range required: " << minBatteryRange << " km" << endl;
    } else {
        cout << "No path exists between the cities." << endl;
    }

    
    // Complejidad: O(V + E)
    int L;
    cout << "Enter the battery range (L): ";
    cin >> L;

    if (isRouteFeasible(graph, s, t, L)) {
        cout << "A feasible route exists with battery range " << L << " km." << endl;
    } else {
        cout << "No feasible route exists with battery range " << L << " km." << endl;
    }

    return 0;
}