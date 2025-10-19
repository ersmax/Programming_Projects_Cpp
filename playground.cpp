#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <limits>

using namespace std;

// Load file with rows: <age> <maleProb> <femaleProb>
// Fills vectors so that male[age] and female[age] are available.
// Returns true on success.
bool loadProbabilities(const string& path, vector<double>& male, vector<double>& female) {
    ifstream in(path);
    if (!in) return false;
    male.clear(); female.clear();
    int age;
    double m, f;
    int maxAge = -1;
    // read rows (skip headers if present by checking first token)
    while (in >> age >> m >> f) {
        if (age < 0) continue;
        if (age > maxAge) {
            male.resize(age + 1, numeric_limits<double>::quiet_NaN());
            female.resize(age + 1, numeric_limits<double>::quiet_NaN());
            maxAge = age;
        }
        male[age] = m;
        female[age] = f;
    }
    return !male.empty();
}

// Simulate death age starting at 'startAge' for sex 'M' or 'F'.
// Uses provided RNG. If probability for an age is NaN/missing, treats it as zero (no death).
int simulate(int startAge, char sex, const vector<double>& male, const vector<double>& female, mt19937& rng) {
    if (startAge < 0) return 0;
    const int maxAge = static_cast<int>(max(male.size(), female.size())) - 1;
    uniform_real_distribution<double> dist(0.0, 1.0);
    for (int age = startAge; age <= maxAge; ++age) {
        double p = 0.0;
        if (age < static_cast<int>(male.size()) && age < static_cast<int>(female.size())) {
            p = (sex == 'M' || sex == 'm') ? male[age] : female[age];
            if (!(p == p)) p = 0.0; // NaN -> 0
        }
        double r = dist(rng);
        if (r <= p) return age;
    }
    return maxAge;
}

// Example usage
int main() {
    vector<double> male, female;
    if (!loadProbabilities("LifeDeathProbability.txt", male, female)) {
        cerr << "Failed to load `LifeDeathProbability.txt`\n";
        return 1;
    }

    // seed once
    random_device rd;
    mt19937 rng(rd());

    int age = 30;
    char sex = 'M';
    int deathAge = simulate(age, sex, male, female, rng);
    cout << "Simulated death age: " << deathAge << '\n';
    return 0;
}
