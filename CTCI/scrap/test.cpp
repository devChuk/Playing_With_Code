// """
// Given a completed sudoku board, 9x9 array of arrays containing integers
// between [1, 9], check if the solution is valid or not.
 
// In a valid solution, each column, each row, and each of the nine 3x3 subgrids
// that compose the grid (also called "boxes", "blocks", "regions", or
// "subsquares") contains all of the digits from 1 to 9.
// [https://en.wikipedia.org/wiki/Sudoku]
// """
 
 
// def sudoku_is_valid(board):
//     raise NotImplementedError
 
// if __name__ == '__main__':
//     VALID_SOLUTIONS = [
//         [
//             [9, 1, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 3, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ]
//     ]
 
//     INVALID_SOLUTIONS = [
//         [
//             [9, 9, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 3, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ], [
//             [9, 0, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 3, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ], [
//             [9, 1, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 9, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ],
//     ]
//     for valid_solution in VALID_SOLUTIONS:
//         assert(sudoku_is_valid(valid_solution))
//     for invalid_solution in INVALID_SOLUTIONS:
//         assert(not sudoku_is_valid(invalid_solution))
//     print('Tests pass!')

#include <vector>

bool sudoku_is_valid(std::vector<std::vector<int>> board) {
    // check all rows
        // loop through each row

    std::vector<bool> numberCheck;
    for (int i = 1; i < 10; i++) {
        numberCheck.push_back(false);
    }

    // ROWS
    for (int i = 0; i < board.size(); i++) {
        for (int z = 1; z < 10; z++) {
            numberCheck[z] = false;
        }

        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] >= 1 || board[i][j] <= 9)
                numberCheck[board[i][j]] = true;
            else
                return false;
        }

        for (int c = 0; c < numberCheck.size(); c++) {
            if (!numberCheck[c]) {
                return false;
            }
        }
    }

    // COLUMNS
    for (int i = 0; i < board.size(); i++) {
        for (int z = 1; z < 10; z++) {
            numberCheck[z] = false;
        }

        for (int j = 0; j < board.size(); j++) {
            if (board[j][i] >= 1 || board[j][i] <= 9)
                numberCheck[board[j][i]] = true;
            else
                return false;
        }

        for (int c = 0; c < numberCheck.size(); c++) {
            if (!numberCheck[c]) {
                return false;
            }
        }
    }

    // BOXES
    for (int i = 0; i < board.size(); i++) {
        for (int z = 1; z < 10; z++) {
            numberCheck[z] = false;
        }

        int cornerX = (i / 3) * 3;
        int cornerY = (i % 3) * 3;

        for (int j = 0; j < board.size(); j++) {
            int addX = j / 3;
            int addY = j % 3;

            int x = cornerX + addX;
            int y = cornerY + addY;

            if (board[x][y] >= 1 || board[x][y] <= 9)
                numberCheck[board[x][y]] = true;
            else
                return false;
        }

        for (int c = 0; c < numberCheck.size(); c++) {
            if (!numberCheck[c]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    int VALID_SOLUTIONS[][9] = {
            {9, 1, 6, 8, 4, 3, 5, 2, 7},
            {8, 4, 2, 7, 5, 6, 9, 3, 1},
            {7, 5, 3, 2, 9, 1, 8, 6, 4},
            {3, 6, 4, 9, 2, 7, 1, 8, 5},
            {2, 8, 1, 5, 6, 4, 7, 9, 3},
            {5, 9, 7, 1, 3, 8, 2, 4, 6},
            {6, 7, 8, 4, 1, 9, 3, 5, 2},
            {4, 2, 9, 3, 7, 5, 6, 1, 8},
            {1, 3, 5, 6, 8, 2, 4, 7, 9},
    };
    //     VALID_SOLUTIONS = [
//         [
//             [9, 1, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 3, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ]
//     ]
 
//     INVALID_SOLUTIONS = [
//         [
//             [9, 9, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 3, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ], [
//             [9, 0, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 3, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ], [
//             [9, 1, 6, 8, 4, 3, 5, 2, 7],
//             [8, 4, 2, 7, 5, 6, 9, 3, 1],
//             [7, 5, 9, 2, 9, 1, 8, 6, 4],
//             [3, 6, 4, 9, 2, 7, 1, 8, 5],
//             [2, 8, 1, 5, 6, 4, 7, 9, 3],
//             [5, 9, 7, 1, 3, 8, 2, 4, 6],
//             [6, 7, 8, 4, 1, 9, 3, 5, 2],
//             [4, 2, 9, 3, 7, 5, 6, 1, 8],
//             [1, 3, 5, 6, 8, 2, 4, 7, 9],
//         ],
//     ]
//     for valid_solution in VALID_SOLUTIONS:
//         assert(sudoku_is_valid(valid_solution))
//     for invalid_solution in INVALID_SOLUTIONS:
//         assert(not sudoku_is_valid(invalid_solution))
//     print('Tests pass!')
}