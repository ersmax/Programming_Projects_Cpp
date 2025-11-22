This project is an extension of Programming Project 4.16. Consider a text file
named scores.txt that contains player scores for a game. A possible sample is
shown next where Ronaldo’s best score is 10400, Didier’s best score is 9800, etc.
Put at least five names and scores in the file.
Ronaldo
10400
Didier
9800
Pele
12300
Kaka
8400
Cristiano
8000
Write a function named getHighScores that takes two array parameters, an array
of strings and an array of integers. The function should scan through the file and
set the string array entry at index 0 to the name of the player with the highest score
and set the integer array entry at index 0 to the score of the player with the highest
score. The string array entry at index 1 should be set to the name of the player with
the second highest score and the integer array entry at index 1 should be set to the
score of the player with the second highest score. Do the same for the entries at
index 2. Together, these two arrays give you the names and scores of the top three
players. In your main function, test the getHighScores function by calling it and
outputting the top three players and scores.

---

## Use of the STL algorithms to copy and sort
In function `mergeSort` the std::copy_n algorithm is used to copy segments of the original array 
into temporary arrays for sorting. 
This is a concise and efficient way to handle array copying without manual loops.
```cpp
void mergeSort(std::string name[], int score[], int size) {
    if (size <= 1) return;

    const int sizeLeft = size / 2;
    const int sizeRight = size - sizeLeft;
    int score1[MAX], score2[MAX];
    std::string name1[MAX], name2[MAX];

    std::copy_n(score, sizeLeft, score1);
    std::copy_n(name, sizeLeft, name1);
    // for (int idx = 0; idx < sizeLeft; ++idx) {
    //     score1[idx] = score[idx];
    //     name1[idx] = name[idx];
    // }
    std::copy_n(score + sizeLeft, sizeRight, score2);
    std::copy_n(name + sizeLeft, sizeRight, name2);
    // for (int idx = 0; idx < sizeRight; ++idx) {
    //     score2[idx] = score[sizeLeft + idx];
    //     name2[idx] = name[sizeLeft + idx];
    // }
    mergeSort(name1, score1, sizeLeft);
    mergeSort(name2, score2, sizeRight);
    merge(score1, name1, sizeLeft, score2, name2, sizeRight, score, name, size);
}
```


## Alternative implementation
One could also use a different implementation of merge sort,
by passing directly the left and right indices instead of copying to temporary arrays.
This would avoid the need for temporary arrays and copying, but would require more complex index management.

