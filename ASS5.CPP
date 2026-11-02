#include <iostream>
using namespace std;

int n, board[20][20];

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1)
            return false;

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        if (board[i][j] == 1)
            return false;

    return true;
}

bool solve(int row, int fixedRow) {
    if (row == n)
        return true;

    if (row == fixedRow)
        return solve(row + 1, fixedRow);

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;

            if (solve(row + 1, fixedRow))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int r, c;

    cout << "Enter board size: ";
    cin >> n;

    if (n <= 0 || n > 20) {
        cout << "Invalid board size.\n";
        return 1;
    }

    cout << "Enter fixed queen row and column (1 to n): ";
    cin >> r >> c;

    if (r < 1 || r > n || c < 1 || c > n) {
        cout << "Invalid position.\n";
        return 1;
    }

    r--;
    c--;

    board[r][c] = 1;

    if (isSafe(r, c) == false) {
        // The fixed queen is the only queen initially,
        // so it is safe by itself.
        cout << "Invalid position.\n";
        return 1;
    }

    if (solve(0, r)) {
        cout << "\nSolution:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << '\n';
        }
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}