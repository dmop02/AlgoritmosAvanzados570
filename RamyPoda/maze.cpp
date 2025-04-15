#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Nodo {
    int x, y, costo, heuristica;
    Nodo(int _x, int _y, int _costo, int _heuristica) : x(_x), y(_y), costo(_costo), heuristica(_heuristica) {}
};

bool isSafe(int x, int y, const vector<vector<int>>& maze, vector<vector<int>>& solution) {
    int M = maze.size();
    int N = maze[0].size();
    return (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1 && solution[x][y] == 0);
}

bool solveMazeBacktracking(int x, int y, const vector<vector<int>>& maze, vector<vector<int>>& solution) {
    int M = maze.size();
    int N = maze[0].size();
    if (x == M - 1 && y == N - 1) {
        solution[x][y] = 1;
        return true;
    }

    if (isSafe(x, y, maze, solution)) {
        solution[x][y] = 1;

        if (solveMazeBacktracking(x + 1, y, maze, solution)) return true;
        if (solveMazeBacktracking(x, y + 1, maze, solution)) return true;
        if (solveMazeBacktracking(x - 1, y, maze, solution)) return true;
        if (solveMazeBacktracking(x, y - 1, maze, solution)) return true;

        solution[x][y] = 0;
        return false;
    }
    return false;
}

int calcularHeuristica(int x, int y, int metaX, int metaY) {
    return abs(metaX - x) + abs(metaY - y);
}

bool solveMazeBranchAndBound(vector<vector<int>>& maze, vector<vector<int>>& solution) {
    int M = maze.size();
    int N = maze[0].size();
    vector<Nodo> nodos;
    nodos.push_back(Nodo(0, 0, 0, calcularHeuristica(0, 0, M - 1, N - 1)));

    while (!nodos.empty()) {
        int mejorIdx = 0;
        for (int i = 1; i < nodos.size(); ++i) {
            if ((nodos[i].costo + nodos[i].heuristica) < (nodos[mejorIdx].costo + nodos[mejorIdx].heuristica)) {
                mejorIdx = i;
            }
        }
        Nodo actual = nodos[mejorIdx];
        nodos.erase(nodos.begin() + mejorIdx);

        int x = actual.x, y = actual.y;
        if (x == M - 1 && y == N - 1) {
            solution[x][y] = 1;
            return true;
        }

        if (isSafe(x, y, maze, solution)) {
            solution[x][y] = 1;
            int movimientos[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
            for (int i = 0; i < 4; ++i) {
                int nx = x + movimientos[i][0], ny = y + movimientos[i][1];
                if (isSafe(nx, ny, maze, solution)) {
                    nodos.push_back(Nodo(nx, ny, actual.costo + 1, calcularHeuristica(nx, ny, M - 1, N - 1)));
                }
            }
        }
    }
    return false;
}

void printSolution(const vector<vector<int>>& solution) {
    for (const auto& row : solution) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<int>> maze(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
        }
    }

    vector<vector<int>> solution(M, vector<int>(N, 0));

    cout << "Solución utilizando Backtracking:" << endl;
    if (solveMazeBacktracking(0, 0, maze, solution)) {
        printSolution(solution);
    } else {
        cout << "No existe solución." << endl;
    }

    solution = vector<vector<int>>(M, vector<int>(N, 0));

    cout << "Solución utilizando Ramificación y Poda:" << endl;
    if (solveMazeBranchAndBound(maze, solution)) {
        printSolution(solution);
    } else {
        cout << "No existe solución." << endl;
    }

    return 0;
}
