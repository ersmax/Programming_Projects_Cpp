/*
A common memory matching game played by young children is to start with a
deck of cards that contains identical pairs. For example, given six cards in the deck,
two might be labeled “1”, two might be labeled “2”, and two might be labeled “3”.
The cards are shuffled and placed facedown on the table. The player then selects
two cards that are facedown, turns them faceup, and if they match they are left
faceup. If the two cards do not match, they are returned to their original position
facedown. The game continues in this fashion until all cards are faceup.
Write a program that plays the memory matching game. Use 16 cards that are
laid out in a 4 * 4 square and are labeled with pairs of numbers from 1 to 8. Your
program should allow the player to specify the cards through a coordinate system.
For example, in the following layout:

| cards | 1 | 2 | 3 | 4 |
|---:|:--:|:--:|:--:|:--:|
| 1 | 8 | * | * | * |
| 2 | * | * | * | * |
| 3 | * | 8 | * | * |
| 4 | * | * | * | * |

all of the cards are facedown except for the pair of 8’s, which has been located at
coordinates (1,1) and (2,3). To hide the cards that have been temporarily placed
faceup, output a large number of newlines that force the old board off the screen.
Hint: Use a 2D array for the arrangement of cards and another 2D array that indicates
whether a card is faceup or facedown. Write a function that “shuffles” the
cards in the array by repeatedly selecting two cards at random and swapping them.
*/

#include <iostream>
#include <random>
#include <sstream>


constexpr int ROWS = 4;
constexpr int COLS = 4;
constexpr int CARDS = ROWS * COLS;
constexpr int SAME = 2;
constexpr int COORDINATES = 2;
constexpr char FOLD = '*';
constexpr char UNFOLD = '#';

void createBoard(int cards[][COLS], char upDown[][COLS], int nRows);
void shuffleCards(int cards[][COLS], int nRows);
void showBoard(const int cards[][COLS], const char upDown[][COLS], int nRows);
bool chooseCards(int nRows, int nCols, int card1[], int card2[], int dimensions);
void unfold(const int cards[][COLS], char upDown[][COLS], int nRows,
            const int card1[], const int card2[], int dimensions, int& remainingCards);
void clearConsole();

int main( ) {
    int board[ROWS][COLS] = {0};
    char upDown[ROWS][COLS];
    int card1[2], card2[2];
    int unmatchedCards = CARDS;
    createBoard(board, upDown, ROWS);
    shuffleCards(board, ROWS);
    showBoard(board, upDown, ROWS);

    while (chooseCards(ROWS, COLS, card1, card2, COORDINATES) ||
           unmatchedCards > 0) {
        unfold(board, upDown, ROWS, card1, card2, COORDINATES, unmatchedCards);
        showBoard(board, upDown, ROWS);
    }
    if (unmatchedCards == 0) std::cout << "You won!\n";
    else                     std::cout << "Game over\n";

    std::cout << "\n";
    return 0;
}

void createBoard(int cards[][COLS], char upDown[][COLS], const int nRows) {
    int cardValue = 1;
    for (int row = 0; row < nRows; ++row)
        for (int col = 0; col < COLS; col++) {
            if (col % SAME == 0)
                cards[row][col] = cardValue;
            else
                cards[row][col] = cardValue++;
            upDown[row][col] = FOLD;
        }
}

void shuffleCards(int cards[][COLS], int nRows) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    // Fisher-Yates on flattened indices
    for (int card = CARDS - 1; card > 0; --card) {
        std::uniform_int_distribution<int>dist(0, card);
        const int randomCard = dist(gen);
        const int rowRandomCard = randomCard / COLS;
        const int colRandomCard = randomCard % COLS;
        const int rowCard = card / COLS;
        const int colCard = card % COLS;
        std::swap(cards[rowCard][colCard],
                  cards[rowRandomCard][colRandomCard]);
    }
}

void showBoard(const int cards[][COLS], const char upDown[][COLS], int nRows) {
    // Print header
    std::cout << "   ";
    for (int col = 0; col < COLS; ++col)
        std::cout << (col + 1) << " ";
    std::cout << "\n";
    std::cout << "   ";
    for (int col = 0; col < COLS; ++col)
        std::cout << "--";
    std::cout << "\n";


    for (int row = 0; row < nRows; ++row) {
        std::cout << (row + 1);
        std::cout << " |";
        for (int col = 0; col < COLS; ++col) {
            if (upDown[row][col] == FOLD)  std::cout << FOLD << " ";
            else                           std::cout << cards[row][col] << " ";
        }
        std::cout << "\n";
    }

    // Show true values. DEBUG ONLY
    // for (int row = 0; row < nRows; ++row) {
    //     for (int col = 0; col < COLS; ++col)
    //         std::cout << cards[row][col] << " ";
    //     std::cout << "\n";
    // }
}

bool chooseCards(const int nRows, const int nCols, int card1[], int card2[], const int dimensions) {
    std::string line;
    for (int pick = 1; pick <= dimensions; ++pick) {
        while (true) {
            std::cout << "Enter row and column of card " << pick
                      << " (1.." << nRows << " 1.." << nCols << ")\n"
                      << "(Or type `exit` to end the program)\n";
            // EOF or input error
            if (!std::getline(std::cin,line)) {
                std::cout << "End of input\n";
                return false;
            }
            if (line == "exit")
                return false;

            std::istringstream iss(line);
            int row, col;
            if (!(iss >> row >> col)) {
                std::cout << "Invalid input. Retry\n";
                continue;
            }
            --row;
            --col;
            if (row < 0 || row >= nRows || col < 0 || col >= nCols) {
                std::cout << "No valid card selected. Retry\n";
                continue;
            }
            // do not pick the same card
            if (pick == 2 && row == card1[0] && col == card1[1]) {
                std::cout << "Choose a different card.\n";
                continue;
            }
            switch (pick) {
                case 1:
                    card1[0] = row;
                    card1[1] = col;
                    break;
                case 2:
                    card2[0] = row;
                    card2[1] = col;
                    break;
                default:
                    break;
            }
            break;
        }
    }
    return true;
}

void unfold(const int cards[][COLS], char upDown[][COLS], const int nRows,
            const int card1[], const int card2[], const int dimensions, int& remainingCards) {

    const int rowCard1 = card1[0], colCard1 = card1[1];
    const int rowCard2 = card2[0], colCard2 = card2[1];

    bool card1seen = false, card2seen = false;
    if (upDown[rowCard1][colCard1] == UNFOLD) card1seen = true;
    if (upDown[rowCard2][colCard2] == UNFOLD) card2seen = true;



    upDown[rowCard1][colCard1] = UNFOLD;
    upDown[rowCard2][colCard2] = UNFOLD;
    if (cards[rowCard1][colCard1] == cards[rowCard2][colCard2]) {
        remainingCards -= 2;
        std::cout << "Found a match!\n";
        return;
    }
    // for unpaired match, show and then hide pair
    showBoard(cards, upDown, nRows);
    std::cout << "Cards do not match. Press `Enter` to continue\n";
    std::string keystroke;
    std::getline(std::cin, keystroke);
    if (!card1seen)
        upDown[rowCard1][colCard1] = FOLD;
    if (!card2seen)
        upDown[rowCard2][colCard2] = FOLD;

    clearConsole();
}

void clearConsole() {
    for (int idx = 0; idx < 8; ++idx) std::cout << "\n";
}
