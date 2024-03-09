#include <iostream>
using namespace std;

const int N = 9;

// Print Sudoku Grid
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}
// Check if it is safe to put a number in the grid
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    // Check if the number is present or not in the current subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Solve using backtracking
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Locate empty cell
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty)
            break;
    }

    if (!isEmpty)
        return true;

    // Brute force all numbers from 1 to 9 and check if it is safe to place
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            // Reset if solution is not possible
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    // Enter your Puzzle here. 0 represents an empty cell
    int grid[N][N] = {
        {0, 4, 9, 0, 0, 0, 2, 3, 0},
        {0, 1, 0, 0, 2, 0, 7, 0, 8},
        {3, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 6, 0, 0, 0, 0, 9, 0, 4},
        {4, 0, 0, 0, 0, 0, 0, 1, 5},
        {0, 0, 0, 6, 1, 4, 0, 7, 0},
        {0, 3, 0, 0, 0, 2, 0, 5, 0},
        {0, 8, 0, 4, 3, 0, 0, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    if (solveSudoku(grid))
        printGrid(grid);
    else
        cout << "Solution does not exist" << endl;

    return 0;
}
