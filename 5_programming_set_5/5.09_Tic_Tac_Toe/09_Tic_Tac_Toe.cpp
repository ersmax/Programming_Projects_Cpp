/*
Write a program that will allow two users to play tic-tac-toe. The program should
ask for moves alternately from player X and player O. The program displays the
game positions as follows:
1 2 3
4 5 6
7 8 9
The players enter their moves by entering the position number they wish to mark.
After each move, the program displays the changed board. A sample board configuration
is as follows:
X X O
4 5 6
O 8 9
*/

#include <iostream>
#include <random>
#include <limits>

constexpr int PLAYERS = 2;
constexpr int N_ROWS = 3;
constexpr int N_COLS = 3;
constexpr int MOVES = 5;

void initializeBoard(int board[][N_COLS], int nRows);

void showBoard(const int board[][N_COLS], int nRows);

void playTurn(int board[][N_COLS], int nRows,
                int movesPlayer[], int& nMoves,
                int idxPlayer);

int enterMove(const int board[][N_COLS], int nRows);

void changePlayer(int nPlayers, int& idxPlayer);

bool isBusy(const int board[][N_COLS], int nRows, int position);

int main( ) {
    char player[PLAYERS] = {'0','X'};     // player O = 0, player X = -1
    int board[N_ROWS][N_COLS];
    int placesLeft = N_ROWS * N_COLS;
    int movesPlayerX[MOVES] = {};
    int nMovesX = 0;
    int movesPlayerO[MOVES] = {};
    int nMovesY = 0;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> playerNumber(0, 1);
    int playerTurn  = playerNumber(rng);

    initializeBoard(board, N_ROWS);
    while (placesLeft > 0) {

        char namePlayer = player[playerTurn];
        if (namePlayer == '0')
            playTurn(board, N_ROWS, movesPlayerO, nMovesY, 0);
        else if (namePlayer == 'X')
            playTurn(board, N_ROWS, movesPlayerX, nMovesX, -1);

        changePlayer(PLAYERS, playerTurn);
        --placesLeft;
    }

    showBoard(board, N_ROWS);

    std::cout << "\n";
    return 0;
}

void initializeBoard(int board[][N_COLS], int nRows) {
    int n = 0;
    for (int row = 0; row < nRows; ++row)
        for (int col = 0; col < N_COLS; ++col)
            board[row][col] = ++n;
}

void playTurn(int board[][N_COLS], const int nRows,
              int movesPlayer[], int& nMoves,
              const int idxPlayer) {

    int movePlace = enterMove(board, nRows);
    movesPlayer[nMoves++] = movePlace;
    int row = (movePlace - 1) / nRows;
    int col = (movePlace - 1) % nRows;
    board[row][col] = idxPlayer;
}

int enterMove(const int board[][N_COLS], const int nRows) {
    int next;
    while (true) {
        showBoard(board, nRows);
        std::cout << "Enter a valid move:\n";
        if (!(std::cin >> next)) {
            std::cout << "Not a number\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }
        // consume remaining input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // check position in the grid
        if ((next < 1) || (next > nRows * N_COLS)) {
            std::cout << "Not a valid position\n";
            continue;
        }

        // check position is free.
        if (isBusy(board, nRows, next)) {
            std::cout << "Position already chosen. Retry\n";
            continue;
        }

        return next;
    }
}

void showBoard(const int board[][N_COLS], const int nRows) {

    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < N_COLS; ++col) {
            if (board[row][col] == 0)
                std::cout << 'O' << " ";
            else if (board[row][col] == -1)
                std::cout << 'X' << " ";
            else
                std::cout << board[row][col] << " ";

        }
        std::cout << "\n";
    }
}

void changePlayer(const int nPlayers, int& idxPlayer) {
    idxPlayer = (idxPlayer + 1) % nPlayers;
}

bool isBusy(const int board[][N_COLS], int nRows, int position) {
    int row = (position - 1) / nRows;
    int col = (position - 1) % N_COLS;
    return (board[row][col] < 1);
}
