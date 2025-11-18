/*
The mathematician John Horton Conway invented the “Game of Life.” Though
not a “game” in any traditional sense, it provides interesting behavior that is
specified with only a few rules. This project asks you to write a program that allows
you to specify an initial configuration. The program follows the rules of Life (listed
shortly) to show the continuing behavior of the configuration.
LIFE is an organism that lives in a discrete, two-dimensional world. While this
world is actually unlimited, we do not have that luxury, so we restrict the array to
80 characters wide by 22 character positions high. If you have access to a larger
screen, by all means use it.
This world is an array with each cell capable of holding one LIFE cell. Generations
mark the passing of time. Each generation brings births and deaths to the LIFE
community. The births and deaths follow this set of rules:
1. We define each cell to have eight neighbor cells. The neighbors of a cell are the
   cells directly above, below, to the right, to the left, diagonally above to the right
   and left, and diagonally below, to the right and left.
2. If an occupied cell has zero or one neighbor, it dies of loneliness. If an occupied
   cell has more than three neighbors, it dies of overcrowding.
3. If an empty cell has exactly three occupied neighbor cells, there is a birth of a
   new cell to replace the empty cell.
4. Births and deaths are instantaneous and occur at the changes of generation.
   A cell dying for whatever reason may help cause birth, but a newborn cell cannot
   resurrect a cell that is dying, nor will a cell’s death prevent the death of another, say,
   by reducing the local population.

Examples:

| Initial Configuration | Generation 1 | Generation 2 | Generation 3 |
|----------------------:|:-------------|:-------------|:-------------|
|                       | *            |              | *            |
|                   *** | *            | ***          | *            |
|                       | *            |              | *            |

and so on.

Notes: Some configurations grow from relatively small starting configurations.
Others move across the region. It is recommended that for text output you use
a rectangular char array with 80 columns and 22 rows to store the LIFE world’s
successive generations. Use an * to indicate a living cell and use a blank to indicate
an empty (or dead) cell. If you have a screen with more rows than that, by all means
make use of the whole screen.
Suggestions: Look for stable configurations. That is, look for communities that repeat
patterns continually. The number of configurations in the repetition is called
the period. There are configurations that are fixed, that is, that continue without
change. A possible project is to find such configurations.
Hints: Define a void function named generation that takes the array we call
world, an 80-column by 22-row array of type char, which contains the initial
configuration. The function scans the array and modifies the cells, marking the
cells with births and deaths in accord with the rules listed previously. This involves
examining each cell in turn and either killing the cell, letting it live, or, if the cell
is empty, deciding whether a cell should be born. There should be a function
display that accepts the array world and displays the array on the screen. Some
sort of time delay is appropriate between calls to generation and display. To
do this, your program should generate and display the next generation when you
press Return. You are at liberty to automate this, but automation is not necessary
for the program.
*/

#include <iostream>


void generation();

constexpr int ROW = 22;
constexpr int COL = 80;
constexpr char FILL = '*';
constexpr char EMPTY = ' ';

void startGrid(char grid[][COL], int nRows, int& busyPosition);

void generation(char grid[][COL], int nRows, int& busyPosition);

void display(const char grid[][COL], int nRows, int busyPosition);

int main( ) {
   char world[ROW][COL] = {EMPTY};
   int busyCells = 0;
   startGrid(world, ROW, busyCells);

   while (busyCells > 0) {
      generation(world, ROW, busyCells);
      display(world, ROW, busyCells);
   }
   std::cout << "\n";
   return 0;
}


