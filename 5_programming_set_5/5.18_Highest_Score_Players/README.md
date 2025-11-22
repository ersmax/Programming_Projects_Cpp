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

## Alternative implementation
One could also use a different implementation of merge sort,
by creating temporary arrays for left and right subpartitions.
This would need copying and potentially overflow. 
Below is an example of such an implementation.
The alternative code in the program provided is dangerous for a number of reasons:

1. Memory Efficiency (Most Important Difference)
   - The program allocates one auxiliary buffer (tempName, tempScore) once, 
     and reuses it in all recursive calls. 
   - The alternative allocates two full-size arrays (score1, score2, name1, name2) 
     on every recursive call. This means:
     - O(n log n) extra memory usage 
     - Heavy stack frame usage 
     - Potential stack overflow for large MAX

2. Huge unnecessary copying 
   - The program uses optimal memory: O(n). 
   - The alternative is far more expensive: O(n log n).

3. Performance / Speed 
   - The program copies each element only when merging (typical merge sort cost). 
   - The alternative copies half the array twice per recursion, leading to way more copies. 
     This makes it significantly slower for large arrays.

4. Cache efficiency 
   - The program accesses memory more sequentially and keeps its working data local. 
   - The alternative constantly copies subarrays, which tends to cause cache inefficiency.

5. Code structure
   - The program uses classical top-down merge sort pattern with shared temporary workspace. 
     Less risk of bugs. 
   - The alternative is easier to read conceptually but highly inefficient. 
     Hard-coded `[MAX] size` arrays inside each recursion are dangerous for large input.

6. Practical C++ considerations
   - The program avoids repeated large allocations and copies.
   - The alternative:
     - is not scalable, 
     - copies potentially expensive std::string objects repeatedly. 
     - has higher overhead and memory churn.


```cpp
void orderData(std::string name[], int score[], const int size) {
    if (size <= 1) return;
    mergeSort(name, score, size);
}

void mergeSort(std::string name[], int score[], int size) {
    if (size <= 1) return;

    const int sizeLeft = size / 2;
    const int sizeRight = size - sizeLeft;
    int score1[MAX], score2[MAX];
    std::string name1[MAX], name2[MAX];

    std::copy_n(score, sizeLeft, score1);
    std::copy_n(name, sizeLeft, name1);
    std::copy_n(score + sizeLeft, sizeRight, score2);
    std::copy_n(name + sizeLeft, sizeRight, name2);
    mergeSort(name1, score1, sizeLeft);
    mergeSort(name2, score2, sizeRight);
    merge(score1, name1, sizeLeft, score2, name2, sizeRight, score, name, size);
}

void merge(const int arr1[], const std::string name1[], const int size1,
           const int arr2[], const std::string name2[], const int size2,
           int result[], std::string names[], const int totSize) {

    int p1 = 0, p2 = 0, idx = 0;
    while ((p1 < size1) && (p2 < size2) && (idx < totSize)) {
        if (arr1[p1] >= arr2[p2]) {
            result[idx] = arr1[p1];
            names[idx] = name1[p1];
            ++p1;
        } else {
            result[idx] = arr2[p2];
            names[idx] = name2[p2];
            ++p2;
        }
        ++idx;
    }
    // Merge wrap-up
    while ((p1 < size1) && (idx < totSize)) {
        result[idx] = arr1[p1];
        names[idx] = name1[p1];
        ++p1;
        ++idx;
    }
    while ((p2 < size2) && (idx < totSize)) {
        result[idx] = arr2[p2];
        names[idx] = name2[p2];
        ++p2;
        ++idx;
    }
}
```

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

    // std::copy_n(score, sizeLeft, score1);
    // std::copy_n(name, sizeLeft, name1);
    for (int idx = 0; idx < sizeLeft; ++idx) {
        score1[idx] = score[idx];
        name1[idx] = name[idx];
    }
    // std::copy_n(score + sizeLeft, sizeRight, score2);
    // std::copy_n(name + sizeLeft, sizeRight, name2);
    for (int idx = 0; idx < sizeRight; ++idx) {
        score2[idx] = score[sizeLeft + idx];
        name2[idx] = name[sizeLeft + idx];
    }
    mergeSort(name1, score1, sizeLeft);
    mergeSort(name2, score2, sizeRight);
    merge(score1, name1, sizeLeft, score2, name2, sizeRight, score, name, size);
}
```