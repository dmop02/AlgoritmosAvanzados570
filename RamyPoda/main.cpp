#include <iostream>
#include <vector>

// Function to check if a given position is valid in the maze
bool isValid(int x, int y, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N);
}

// Function to solve the maze using backtracking
bool solveMaze(const std::vector<std::vector<int>>& maze, std::vector<std::vector<int>>& path, int x, int y, int M, int N) {
    // If the current position is the goal, return true
    if (x == M - 1 && y == N - 1) {
        path[x][y] = 1;
        return true;
    }

    // Check if the current position is valid and a valid move
    if (isValid(x, y, M, N) && maze[x][y] == 1) {
        // Mark the current position as part of the path
        path[x][y] = 1;

        // Move right
        if (solveMaze(maze, path, x, y + 1, M, N))
            return true;

        // Move down
        if (solveMaze(maze, path, x + 1, y, M, N))
            return true;

        // If none of the above moves work, backtrack
        path[x][y] = 0;
        return false;
    }

    return false;
}

int main() {
    int M, N;
    std::cin >> M >> N;

    std::vector<std::vector<int>> maze(M, std::vector<int>(N));
    std::vector<std::vector<int>> path(M, std::vector<int>(N, 0));

    // Read the maze from input
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> maze[i][j];
        }
    }

    // Solve the maze
    if (solveMaze(maze, path, 0, 0, M, N)) {
        // Print the path
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << path[i][j] << " ";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "No path found!" << std::endl;
    }

    return 0;
}


