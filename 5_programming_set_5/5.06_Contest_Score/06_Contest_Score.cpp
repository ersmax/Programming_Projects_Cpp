/*
On a popular television dance show, each contestant is given scores based on 4
parameters: technicality, expression, stage utilization, and the energy level of the
contestant. The jury of 3 judges award scores of 1 to 10 against each parameter, with
10 being the highest. All the scores given by a judge are summed up and averaged
against the scores given by the other judges to obtain each contestant’s final score.
Write a computer program that inputs scores given by each judge against all the
parameters and calculates the overall score obtained by a contestant. The program
should ensure that all inputs are within the allowable data ranges.
*/

#include <array>
#include <iostream>
#include <string>
#include <limits>
#include <cassert>

constexpr int JUDGES = 3;
constexpr int PARAMETERS = 4;
const std::array<std::string, PARAMETERS> NAME_PARAMETERS = {
    "Technicality", "Expression", "Stage Utilization", "Energy level" };


void fillData(double score[][PARAMETERS], int nJudges);

void computeJudgeAvg(const double score[][PARAMETERS], int nJudges,
                     double judgeAvg[], int numJudges);

void computeParameterAvg(const double score[][PARAMETERS], int nJudges,
                         double parameterAvg[], int nParameters);

void display();

int main( ) {
    double score[JUDGES][PARAMETERS] = {};
    double judgeAvg[PARAMETERS];
    double parameterAvg[JUDGES];

    fillData(score, JUDGES);

    for (const double (&judge)[PARAMETERS] : score)
        for (const double singleScore : judge)
            assert((singleScore >= 0) && (singleScore <= 10));
    computeJudgeAvg(score, JUDGES, judgeAvg, JUDGES);
    computeParameterAvg(score, JUDGES, parameterAvg, PARAMETERS);
    // TODO: computeParticipantAvg();
    // TODO: displayResults();

    std::cout << "\n";
    return 0;
}

void fillData(double score[][PARAMETERS], const int nJudges) {
    double next;

    for (int judge = 0; judge < nJudges; ++judge) {

        for (int nParameter = 0; nParameter < PARAMETERS; ++nParameter) {
            std::cout << "Enter vote (0-10) for " << NAME_PARAMETERS[nParameter]
                      << " for judge " << judge + 1 << ":\n";

            while (true) {
                if (!(std::cin >> next)) {
                    std::cout << "Invalid value for " << NAME_PARAMETERS[nParameter]
                                  << ". Retry.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                // ignore remaining input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if ((next >= 0) && (next <= 10)) {
                    score[judge][nParameter] = next;
                    break;
                }
                std::cout << "Score for " << NAME_PARAMETERS[nParameter]
                           << " must be greater than (or equal) 0 and less than (or equal) 10\n";
            }
        }
    }
}

void computeJudgeAvg(const double score[][PARAMETERS], const int nJudges,
                    double judgeAvg[], int numJudges) {

    for (int judge = 0; judge < numJudges; ++judge) {
        double sum = 0;
        for (int parameter = 0; parameter < PARAMETERS; ++parameter)
            sum += score[judge][parameter];

        const double avgJudge = sum / PARAMETERS;
        judgeAvg[judge] = avgJudge;
    }
}

void computeParameterAvg(const double score[][PARAMETERS], int nJudges,
                         double parameterAvg[], int nParameters) {

    for (int parameter = 0; parameter < nParameters; ++parameter)
}


