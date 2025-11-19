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

---

## Implementation notes

- `startGrid(char grid[][COL], int nRows, int& busyPosition)`
  - Places initial patterns (pulsar and small ship) into `grid`.
  - Uses `setCell` to guard bounds and increment `busyPosition` for each live cell.

- `setCell(char grid[][COL], const int nRows, int row, int col, int& busyPosition)`
  - Checks `inBounds` for row and col.
  - Sets `grid[row][col]` to `FILL` and increments `busyPosition` if cell was previously empty.

- `display(const char grid[][COL], const int nRows)`
  - Writes `nRows` rows of the grid to `stdout` and sleeps a short duration to animate.

- `generation(char grid[][COL], const int nRows, int& busyPosition)`
  - Builds `nextGenGrid` initialized to `EMPTY`.
  - Uses small helpers (implemented as lambdas in the code) to test and set cells:
    - `alive` — checks whether a cell is `FILL`.
    - `isBorn` — marks a cell `FILL` and increments local `newBorn`.
    - `die` — marks a cell `EMPTY`.
  - For each cell, counts neighbors via `countNeighbors` and applies the Game of Life rules to `nextGenGrid`.
  - Copies the computed rows back into `grid` and updates `busyPosition` with the number of new live cells.
  - Note: copy should copy only the `nRows * COL` characters (either `std::copy_n` or `std::memcpy` with the correct byte count) to avoid copying unused rows.

- `countNeighbors(int row, int col, const char grid[][COL], int nRows)`
  - Iterates the 3x3 neighborhood, uses `inBounds` to skip outside cells and ignores the center cell.
  - Returns the number of neighboring `FILL` cells.

- `inBounds(int idxCell, int limit)`
  - Simple range check: `idxCell >= 0 && idxCell < limit`.

---

## Lambda vs separate functions
A lambda is an inline, unnamed function object that can capture local variables from the surrounding scope. 
Example form used in `generation` function:
```cpp
auto alive = [](char organism) { 
   return organism == FILL; 
};
```
```cpp
auto isBorn = [&](char& cell) { 
   cell = FILL; ++newBorn; 
};
```  
The `&` capture allows `isBorn` to update the local `newBorn` counter without passing it explicitly.
This allows me to update the number of total `organisms` living in the grid, hence ending the 
loop or repeat it indefinitely on the basis of such living cells.

### Separate functions alternative
The alternative is to define regular functions in file scope.
Functions signature:
```cpp
bool alive(char organism);
void die(char& organism);
void isBorn(char& organism, int& countAlive);
```
Functions definition:
```cpp
bool alive(const char organism) {
   return (organism == FILL);
}
void die(char& organism) {
   organism = EMPTY;
}
void isBorn(char& organism, int& countAlive) {
   organism = FILL;
   ++countCountAlive;
}
```

### Comparison

- Lambdas (used in `generation`)
   - Pros:
      - Local scope: helpers are defined next to the algorithm that uses them (better locality).
      - Can capture local variables (e.g., `newBorn`) directly; no extra parameters needed (better readability).
      - Avoid polluting global/function-scope namespace.
   - Cons:
      - Small, one-off helpers — not ideal if reuse or unit testing is needed (not a big deal here).
      - Slightly less discoverable if overused inline (can be misleading).

- Separate functions
   - Pros:
      - Reusable and easier to test independently.
      - Clear function signatures and potentially more readable if logic is non-trivial.
   - Cons:
      - Cannot capture local variables — we must pass references or make state global.

### Notes
- I decided to try lambdas in `generation` because they are short, closely tied to the algorithm, 
  and need to update the new organisms, `newBorn`. If the helper logic grows or is reused elsewhere, 
  we should refactor into separate functions with explicit parameters (or into a small helper class).
- When copying the computed grid, we should use `std::copy_n` for element-wise clarity 
  or `std::memcpy` with an explicit byte count: `nRows * COL * sizeof(char)` if nRows differ between old 
  and new Grid. This is not the case, however.

### Illustrative example

