#include <iostream>
#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<vector<int>>& graph, const vector<int>& colors, int node, int color) {
    for (int i = 0; i < graph.size(); i++) {
        if (graph[node][i] && colors[i] == color) {
            return false;
        }
    }
    return true;
}

bool assignColors(const vector<vector<int>>& graph, vector<int>& colors, int node, int numColors) {
    if (node == graph.size()) {
        return true;
    }

    for (int color = 0; color < numColors; color++) {
        if (isSafe(graph, colors, node, color)) {
            colors[node] = color;
            if (assignColors(graph, colors, node + 1, numColors)) {
                return true;
            }
            colors[node] = -1;
        }
    }
    return false;
}

void printColors(const vector<int>& colors) {
    for (int i = 0; i < colors.size(); i++) {
        cout << "Node: " << i << ", Assigned Color: " << colors[i] << endl;
    }
}

void colorGraph(const vector<vector<int>>& graph) {
    int numNodes = graph.size();
    vector<int> colors(numNodes, -1);
    if (assignColors(graph, colors, 0, numNodes)) {
        printColors(colors);
    } else {
        cout << "No es posible asignar colores a los nodos" << endl;
    }
}

int main() {
    int numNodes;
    cin >> numNodes;
    vector<vector<int>> graph(numNodes, vector<int>(numNodes));
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            cin >> graph[i][j];
        }
    }
    colorGraph(graph);
    return 0;
}
 