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

---