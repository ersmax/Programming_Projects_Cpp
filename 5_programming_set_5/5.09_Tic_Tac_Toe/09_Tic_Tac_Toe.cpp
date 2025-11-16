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

enum class PlayerIndex { O = 0, X = 1};

int boardValue(PlayerIndex player);

char playerChar(PlayerIndex player);

void togglePlayer(PlayerIndex& player);

void initializeBoard(int board[][N_COLS], int nRows);

void showBoard(const int board[][N_COLS], int nRows);

void playTurn(int board[][N_COLS], int nRows,
              int movesPlayer[], int& nMoves,
              PlayerIndex playerNumber);

int enterMove(const int board[][N_COLS], int nRows);

bool isCellBusy(const int board[][N_COLS], int nRows, int position);

int main( ) {
    int board[N_ROWS][N_COLS];
    int placesLeft = N_ROWS * N_COLS;
    int movesPlayerX[MOVES] = {};
    int nMovesX = 0;
    int movesPlayerO[MOVES] = {};
    int nMovesY = 0;

    std::mt19937 rng(std::random_device{}());       // random number generator
    std::uniform_int_distribution<int> playerNumber(0, 1);
    auto playerTurn = static_cast<PlayerIndex>(playerNumber(rng));

    initializeBoard(board, N_ROWS);
    while (placesLeft > 0) {

        if (playerTurn == PlayerIndex::O)
            playTurn(board, N_ROWS, movesPlayerO, nMovesY, playerTurn);
        else if (playerTurn == PlayerIndex::X)
            playTurn(board, N_ROWS, movesPlayerX, nMovesX, playerTurn);

        togglePlayer(playerTurn);
        --placesLeft;
    }

    showBoard(board, N_ROWS);

    std::cout << "\n";
    return 0;
}

int boardValue(const PlayerIndex player) {
    return (player == PlayerIndex::O) ? 0 : -1;
}

char playerChar(const PlayerIndex player) {
    return (player == PlayerIndex::O) ? 'O' : 'X';
}


void initializeBoard(int board[][N_COLS], const int nRows) {
    int num = 0;
    for (int row = 0; row < nRows; ++row)
        for (int col = 0; col < N_COLS; ++col)
            board[row][col] = ++num;
}

void playTurn(int board[][N_COLS], const int nRows,
              int movesPlayer[], int& nMoves,
              const PlayerIndex playerNumber) {

    int movePlace = enterMove(board, nRows);
    movesPlayer[nMoves++] = movePlace;
    int row = (movePlace - 1) / N_COLS;
    int col = (movePlace - 1) % N_COLS;
    board[row][col] = boardValue(playerNumber);
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

        if (isCellBusy(board, nRows, next)) {
            std::cout << "Position already chosen. Retry\n";
            continue;
        }

        return next;
    }
}

void showBoard(const int board[][N_COLS], const int nRows) {

    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < N_COLS; ++col) {
            int cell = board[row][col];

            if (cell == boardValue(PlayerIndex::O))
                std::cout << playerChar(PlayerIndex::O) << " ";

            else if (cell == boardValue(PlayerIndex::X))
                std::cout << playerChar(PlayerIndex::X) << " ";

            else  std::cout << cell << " ";
        }
        std::cout << "\n";
    }
}

void togglePlayer(PlayerIndex& player) {
    player = (player == PlayerIndex::O) ? PlayerIndex::X : PlayerIndex::O;
}

bool isCellBusy(const int board[][N_COLS], const int nRows, const int position) {
    int row = (position - 1) / N_COLS;
    int col = (position - 1) % N_COLS;
    return (board[row][col] < 1);
}
