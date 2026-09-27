#include <iostream>

void printBoard(const char board[3][3])
{
    std::cout << "  0 1 2\n";
    for (int r = 0; r < 3; ++r) {
        std::cout << r << ' ';
        for (int c = 0; c < 3; ++c) std::cout << board[r][c] << ' ';
        std::cout << '\n';
    }
}

char winner(const char board[3][3])
{
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];                                   // row i
        if (board[0][i] != '.' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];                                   // column i
    }
    if (board[1][1] != '.' &&
        ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
         (board[0][2] == board[1][1] && board[1][1] == board[2][0])))
        return board[1][1];                                       // diagonals
    return '.';
}

int main()
{
    char board[3][3];
    for (auto& row : board)
        for (char& cell : row) cell = '.';

    char player = 'X';
    for (int moves = 0; moves < 9;) {
        printBoard(board);
        std::cout << "Player " << player << ", enter row and col: ";
        int r{}, c{};
        if (!(std::cin >> r >> c)) return 0;   // input closed
        if (r < 0 || r > 2 || c < 0 || c > 2 || board[r][c] != '.') {
            std::cout << "Invalid move, try again.\n";
            continue;
        }
        board[r][c] = player;
        ++moves;
        if (winner(board) != '.') {
            printBoard(board);
            std::cout << "Player " << player << " wins!\n";
            return 0;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    printBoard(board);
    std::cout << "It's a draw.\n";
}
