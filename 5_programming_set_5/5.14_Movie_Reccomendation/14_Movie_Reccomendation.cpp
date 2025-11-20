/*
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
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <limits>
#include <cmath>

constexpr int REVIEWERS = 4;
constexpr int MOVIES = 6;
constexpr int CHOICES = 3;
constexpr int FIRST = 100;
constexpr int LAST = 100 + MOVIES - 1;
constexpr double MIN = 1.0;
constexpr double MAX = 5.0;

void fillReviews(int reviews[][MOVIES], int reviewers);
void makeChoice(int choices[], double scoreChoice[], int nMovies, int notSeen[], int notSeenMovies);
void addNotChosen(int notSeen[], int notSeenMovies, const int choices[], int nMovies);
bool movieAlreadyChosen(const int choices[], int nChoices, int code);
bool correctInput(int code, double score);
void predictScore(const int reviews[][MOVIES], int reviewers,
                  const int choices[], const double scoreChoice[], int nChoices,
                  const int notSeen[], double ratingNotSeen[], int notSeenSize);

void computeDistance(const int choices[], const double scoreChoice[], int nChoices,
                     const int reviews[][MOVIES], double distance[], int nReviewers);

void showPrediction(const int notSeen[], const double ratingNotSeen[], int notSeenSize);

int main( ) {
    int reviews[REVIEWERS][MOVIES];
    int choices[CHOICES] = {-1 -1 -1};
    double scoreChoice[CHOICES];
    int notSeen[MOVIES - CHOICES];
    double ratingNotSeen[MOVIES - CHOICES] = {0.0};

    fillReviews(reviews, REVIEWERS);
    makeChoice(choices, scoreChoice, CHOICES, notSeen, MOVIES - CHOICES);
    predictScore(reviews, REVIEWERS, choices, scoreChoice, CHOICES, notSeen, ratingNotSeen, MOVIES - CHOICES);
    showPrediction(notSeen, ratingNotSeen, MOVIES - CHOICES);

    std::cout << "\n";
    return 0;
}

void fillReviews(int reviews[][MOVIES], const int reviewers) {
    const int source[REVIEWERS][MOVIES] = {
        {3, 1, 5, 2, 1, 5},
        {4, 2, 1, 4, 2, 4},
        {3, 1, 2, 4, 4, 1},
        {5, 1, 4, 2, 4, 2},
    };
    std::memcpy(reviews, source, sizeof(source));
}

void makeChoice(int choices[], double scoreChoice[], const int nMovies,
                int notSeen[], int notSeenMovies) {
    int code;
    double score;
    for (int movie = 0; movie < nMovies; ++movie) {
        std::cout << "Enter the movie and rating (1.0-5.0)\n";
        while (true) {
            if (!(std::cin >> code >> score)) {
                std::cout << "Wrong input. Retry\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if (movieAlreadyChosen(choices, movie, code)) continue;
            if (correctInput(code, score)) {
                choices[movie] = code;
                scoreChoice[movie] = score;
                break;
            }
            std::cout << "Wrong values. Retry\n";
        }
    }
    addNotChosen(notSeen, notSeenMovies, choices, nMovies);
}

void addNotChosen(int notSeen[], const int notSeenMovies,
                  const int choices[], const int nMovies) {

    int idxNotSeen = 0;
    for (int movie = FIRST; movie <= LAST && idxNotSeen < notSeenMovies; ++movie) {
        bool chosen = false;

        for (int choice = 0; choice < nMovies; ++choice) {
            if (movie == choices[choice]) {
                chosen = true;
                break;
            }
        }
        if (!chosen) notSeen[idxNotSeen++] = movie;
    }
}

bool movieAlreadyChosen(const int choices[], const int nChoices, const int code) {
    for (int idx = 0; idx < nChoices; ++idx)
        if (choices[idx] == code) {
            std::cout << "Movie already rated. Retry\n";
            return true;
        }
    return false;
}

bool correctInput(const int code, const double score) {
    return ((code >= FIRST) && (code <= LAST) &&
                (score >= MIN) && (score <= MAX));
}

void computeDistance(const int choices[], const double scoreChoice[], const int nChoices,
                     const int reviews[][MOVIES], double distance[], const int nReviewers) {

    // distance for each movie chosen
    for (int choice = 0; choice < nChoices; ++choice) {
        const int codeChoice = choices[choice] - FIRST;
        // consider every reviewer
        for (int reviewer = 0; reviewer < nReviewers; ++reviewer) {
            const double difference = scoreChoice[choice] - reviews[reviewer][codeChoice];
            distance[reviewer] += std::pow(difference, 2);
        }
    }
}

void predictScore(const int reviews[][MOVIES], const int reviewers,
                  const int choices[], const double scoreChoice[], const int nChoices,
                  const int notSeen[], double ratingNotSeen[], const int notSeenSize) {


    double distance[REVIEWERS] = {0.0};
    computeDistance(choices, scoreChoice, nChoices, reviews, distance, REVIEWERS);

    double min = *std::min_element(distance, distance + reviewers);
    int similarRating[REVIEWERS];
    int sizeSimilar = 0;
    for (int reviewer = 0; reviewer < REVIEWERS; ++reviewer)
        if (distance[reviewer] == min) {
            ++sizeSimilar;
            similarRating[reviewer] = reviewer;
        }

    for (int notSeenMovie = 0; notSeenMovie < notSeenSize; ++notSeenMovie) {
        double sum = 0;
        for (int similarPerson = 0; similarPerson < sizeSimilar; ++similarPerson) {
            int reviewer = similarRating[similarPerson];
            int movieCode = notSeen[notSeenMovie];
            int movieIdx = movieCode - FIRST;
            sum = reviews[reviewer][movieIdx];
        }

        ratingNotSeen[notSeenMovie] = sum / sizeSimilar;
    }

    std::cout << "Most similar reviewers:\n";
    for (int idx = 0; idx < sizeSimilar; ++idx)
        std::cout << similarRating[idx] << ", distance: " << distance[idx] << "\n";
}

void showPrediction(const int notSeen[], const double ratingNotSeen[], const int notSeenSize) {
    for (int idx = 0; idx < notSeenSize; ++idx)
        std::cout << "Movie " << notSeen[idx]
                  << ", Predicted Rating: " << ratingNotSeen[idx] << "\n";
}
