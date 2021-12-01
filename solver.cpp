#include <iostream>


// Method to check if a move is valid
bool is_valid_move(int grid[9][9], int row, int col, int choice) {

    // Check if the number is in the same row/column 
    for (int i = 0; i < 9; i++) {
        if (grid[i][col] == choice || grid[row][i] == choice) {
            return false;
        }
    }

    // Row and column box angles
    int row_angle = row - (row % 3);
    int col_angle = col - (col % 3);

    // Check if the number is in the same 3x3 box
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[row_angle + i][col_angle + j] == choice) {
                return false;
            }
        }
    }

    return true;
}


// Method for displaying the sudoku
void display_grid(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
};


// Method to solve the sudoku
bool solve(int grid[9][9], int row, int col) {
    if (col == 9) {
        if (row == 8) {
            std::cout << "Solved sudoku: " << std::endl;
            display_grid(grid);
            return true;
        }

        // Skip to the next row
        col = 0;
        row += 1;
    }

    // Go on
    if (grid[row][col] > 0) {
        return solve(grid, row, col + 1);
    }

    // Try to find a solution
    for (int n = 0; n < 10; n++) {
        if (is_valid_move(grid, row, col, n)) {
            grid[row][col] = n;

            if (solve(grid, row, col + 1)) {
                return true;
            }
        }

        // Restore not valid cells
        grid[row][col] = 0;
    }

    return false;
}


// Method to check if the grid is valid before solving it 
std::pair<int, int> is_valid_grid(int grid[9][9], int row, int col) {

    int choice = grid[row][col];

    // Check if the row and column is valid
    for (int i = 0; i < 9; i++) {
        if ((grid[i][col] == choice || grid[row][i] == choice) && (i != row && i != col)) {
            return std::make_pair(row, col);
        }
    }

    // Check if the box is valid
    int row_angle = row - (row % 3);
    int col_angle = col - (col % 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((grid[row_angle + i][col_angle + j] == choice) && ((row != i + row_angle) && (col != j + col_angle))) {
                return std::make_pair(row, col);
            }
        }
    }

    return { -1, -1 };
}


// Method to check every element of the grid
bool check_grid(int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] != 0) {
                std::pair<int, int> pair = is_valid_grid(grid, i, j);
                if (pair != std::make_pair(-1, -1)) {
                    std::cout << "Grid is not valid. Found an error at row " << pair.first + 1 << ", column " << pair.second + 1 << std::endl;
                    return false;
                }
            }
        }
    }
    return true;
}


// Test with a random  generated sudoku
int main()
{
    int grid[9][9] = {
        {1, 9, 0,    0, 6, 0,    3, 2, 7},
        {0, 2, 0,    1, 9, 0,    0, 0, 0},
        {7, 0, 5,    4, 0, 3,    8, 0, 0},

        {0, 4, 3,    6, 7, 1,    5, 8, 0},
        {2, 0, 0,    0, 4, 0,    0, 0, 0},
        {6, 0, 7,    9, 0, 2,    0, 3, 0},

        {4, 0, 2,    5, 0, 0,    0, 0, 8},
        {0, 0, 6,    0, 0, 4,    0, 1, 5},
        {5, 0, 9,    7, 0, 0,    0, 4, 0}
    };
    
    std::cout << "Generated sudoku: " << std::endl;
    display_grid(grid);
    std::cout << std::endl;
    if (check_grid(grid)) {
        bool solution_found = solve(grid, 0, 0);
        if (!solution_found) {
            std::cout << "No solution found for this sudoku :(";
        }
    }
}
