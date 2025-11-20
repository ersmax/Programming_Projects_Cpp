You have collected reviews from four movie reviewers where the reviewers are
numbered 0–3. Each reviewer has rated six movies where the movies are numbered
100–105. The ratings range from 1 (terrible) to 5 (excellent).
The reviews are shown in the following table:

| Reviewer | 100 | 101 | 102 | 103 | 104 | 105 |
|---------:|:---:|:---:|:---:|:---:|:---:|:---:|
| 0        |  3  |  1  |  5  |  2  |  1  |  5  |
| 1        |  4  |  2  |  1  |  4  |  2  |  4  |
| 2        |  3  |  1  |  2  |  4  |  4  |  1  |
| 3        |  5  |  1  |  4  |  2  |  4  |  2  |

Write a program that stores this data using a 2D array. Based on this information
your program should allow the user to enter ratings for any three movies. The program
should then find the reviewer whose ratings most closely match the ratings
input by the user. It should then predict the user’s interest in the other movies by
outputting the ratings by the reviewer for the movies that were not rated by the
user. Use the Cartesian distance as the metric to determine how close the reviewer’s
movie ratings are to the ratings input by the user. This technique is a simple version
of the nearest neighbor classification algorithm.
For example, if the user inputs a rating of 5 for movie 102, 2 for movie 104, and
5 for movie 105, then the closest match is reviewer 0 with a distance of sqrt
((5 - 5)2 + (2 - 1)2 + (5 - 5)2) = 1. The program would then predict a rating of
3 for movie 100, a rating of 1 for movie 101, and a rating of 2 for movie 103.


