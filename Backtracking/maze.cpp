#include <iostream>
#include <vector>

using namespace std;

// Funcion para verificar movimiento valido
bool isValidMove(const vector<vector<int>>& maze, int row, int col, int M, int N) {
    return (row >= 0 && row < M && col >= 0 && col < N && maze[row][col] == 1);
}

// Funcion para resolver el laberinto utilizando backtracking
bool solveMazeUtil(vector<vector<int>>& maze, int row, int col, int M, int N, vector<vector<int>>& solution) {
    // Si se llega a la salida, se ha encontrado una solucion
    if (row == M - 1 && col == N - 1) {
        solution[row][col] = 1;
        return true;
    }
    if (isValidMove(maze, row, col, M, N)) {
        // Marcar la posicion actual como visitada
        solution[row][col] = 1;
        if (solveMazeUtil(maze, row, col + 1, M, N, solution))
            return true;
        if (solveMazeUtil(maze, row + 1, col, M, N, solution))
            return true;

        
        solution[row][col] = 0;
    }
    return false;
}

// Funcion para resolver el laberinto 
void solveMaze(vector<vector<int>>& maze, int M, int N) {
    vector<vector<int>> solution(M, vector<int>(N, 0));

    if (solveMazeUtil(maze, 0, 0, M, N, solution)) {
        cout << "Path found:" << endl;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << solution[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No path found." << endl;
    }
}

int main() {
    int M, N;
    cout << "Enter the number of rows (M): ";
    cin >> M;
    cout << "Enter the number of columns (N): ";
    cin >> N;

    vector<vector<int>> maze(M, vector<int>(N, 0));

    cout << "Enter the maze (0 or 1, separated by space):" << endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
        }
    }

    solveMaze(maze, M, N);

    return 0;
}