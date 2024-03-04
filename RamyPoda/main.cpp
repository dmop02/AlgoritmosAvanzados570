#include <iostream>
#include <vector>

using namespace std;

bool isValid(int x, int y, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N);
}
// Funcion para resolver el laberinto utilizando backtracking
bool solveMaze(const vector<vector<int>>& maze, vector<vector<int>>& path, int x, int y, int M, int N) {
    if (x == M - 1 && y == N - 1) {
        path[x][y] = 1;
        return true;
    }
    // Revisar si el movimiento es valido
    if (isValid(x, y, M, N) && maze[x][y] == 1) {
        
        path[x][y] = 1;
        
        if (solveMaze(maze, path, x, y + 1, M, N))
            return true;
        if (solveMaze(maze, path, x + 1, y, M, N))
            return true;
        path[x][y] = 0;
        return false;
    }

    return false;
}

int main() {
    int M, N;
    cout << "Enter the number of rows (M): ";
    cin >> M;

    cout << "Enter the number of columns (N): ";
    cin >> N;

    vector<vector<int>> maze(M, vector<int>(N));
    vector<vector<int>> path(M, vector<int>(N, 0));


    cout << "Enter the maze (0 or 1):" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            cin >> maze[i][j];
        }
    }
    // Llamar a la funcion para resolver el laberinto
    if (solveMaze(maze, path, 0, 0, M, N)) {
        cout << "Path found:" << endl;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << path[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}