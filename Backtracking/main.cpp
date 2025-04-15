// Se uso backtracking para resolver el problema de encontrar un camino en un laberinto
// fuente base para el codigo: https://www.geeksforgeeks.org/rat-in-a-maze/
// https://www.geeksforgeeks.org/difference-between-backtracking-and-branch-n-bound-technique/
// Alvaro Solano
// Domingo Mora

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int x, y, cost;
    vector<vector<int>> path;
};
//Complejidad: O(1)
bool isSafe(int x, int y, const vector<vector<int>>& maze) {
    int M = maze.size();
    int N = maze[0].size();
    return (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1);
}
//Complejidad: O(4^(M*N))
bool solveMazeUtil(int x, int y, const vector<vector<int>>& maze, vector<vector<int>>& sol) {
    int M = maze.size();
    int N = maze[0].size();
    if (x == M - 1 && y == N - 1 && maze[x][y] == 1) {
        sol[x][y] = 1;
        return true;
    }

    if (isSafe(x, y, maze)) {
        sol[x][y] = 1;

        if (solveMazeUtil(x + 1, y, maze, sol))
            return true;

        if (solveMazeUtil(x, y + 1, maze, sol))
            return true;

        sol[x][y] = 0;
        return false;
    }

    return false;
}
// Complejidad: O(M*N)
void printSolution(const vector<vector<int>>& sol) {
    for (const auto& row : sol) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}
//Complejidad: O(4^(M*N))
void solveMazeBacktracking(const vector<vector<int>>& maze) {
    int M = maze.size();
    int N = maze[0].size();
    vector<vector<int>> sol(M, vector<int>(N, 0));

    if (solveMazeUtil(0, 0, maze, sol)) {
        printSolution(sol);
    } else {
        cout << "No solution found using backtracking." << endl;
    }
}
// Complejidad: O(M*N)
void solveMazeBranchAndBound(const vector<vector<int>>& maze) {
    int M = maze.size();
    int N = maze[0].size();
    vector<vector<int>> sol(M, vector<int>(N, 0));
    queue<Node> q;

    if (maze[0][0] == 0 || maze[M-1][N-1] == 0) {
        cout << "No solution found using branch and bound." << endl;
        return;
    }

    Node start = {0, 0, 0, sol};
    start.path[0][0] = 1;
    q.push(start);

    int row[] = {1, 0, -1, 0};
    int col[] = {0, 1, 0, -1};

    while (!q.empty()) {
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int cost = node.cost;

        if (x == M - 1 && y == N - 1) {
            printSolution(node.path);
            return;
        }

        for (int k = 0; k < 4; ++k) {
            int newX = x + row[k];
            int newY = y + col[k];

            if (isSafe(newX, newY, maze) && node.path[newX][newY] == 0) {
                Node nextNode = {newX, newY, cost + 1, node.path};
                nextNode.path[newX][newY] = 1;
                q.push(nextNode);
            }
        }
    }

    cout << "No solution found using branch and bound." << endl;
}
//Complejidad: O(M*N)
int main() {
    int M, N;
    cout << "Enter the number of rows (M) and columns (N): ";
    cin >> M >> N;

    vector<vector<int>> maze(M, vector<int>(N));
    cout << "Enter the maze matrix (0 for blocked cell, 1 for open cell):" << endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
        }
    }

    cout << "Solution using Backtracking:" << endl;
    solveMazeBacktracking(maze);

    cout << "Solution using Branch and Bound:" << endl;
    solveMazeBranchAndBound(maze);

    return 0;
}
