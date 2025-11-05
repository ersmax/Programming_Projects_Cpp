In the land of Puzzlevania, Aaron, Bob, and Charlie had an argument over which
one of them was the greatest puzzle-solver of all time. To end the argument once
and for all, they agreed on a duel to the death. Aaron was a poor shot and only hit
his target with a probability of 1/3. Bob was a bit better and hit his target with a
probability of 1/2. Charlie was an expert marksman and never missed. A hit means
a kill and the person hit drops out of the duel.
To compensate for the inequities in their marksmanship skills, the three decided
that they would fire in turns, starting with Aaron, followed by Bob, and then by
Charlie. The cycle would repeat until there was one man standing. That man
would be remembered for all time as the Greatest Puzzle-Solver of All Time.
An obvious and reasonable strategy is for each man to shoot at the most accurate
shooter still alive, on the grounds that this shooter is the deadliest and has the best
chance of hitting back.
Write a program to simulate the duel using this strategy. Your program should use
random numbers and the probabilities given in the problem to determine whether
a shooter hits his target. You will likely want to create multiple subroutines and
functions to complete the problem. Once you can simulate a duel, add a loop to
your program that simulates 10,000 duels. Count the number of times that each
contestant wins and print the probability of winning for each contestant (e.g., for
Aaron your program might output “Aaron won 3595/10,000 duels or 35.95%”).
An alternate strategy is for Aaron to intentionally miss on his first shot. Modify the
program to accommodate this new strategy and output the probability of winning
for each contestant. What strategy is better for Aaron, to intentionally miss on the
first shot or to try and hit the best shooter?

---

function `orderShoot` can also be rewritten more efficiently by using `algorithm` 
from std library. 

```cpp
void orderShoot(vector<pair<string, double> >& participants) {
    std::sort(participants.begin(),
                  participants.end(),
                  [](const pair<string, double>& a,
                     const pair<string, double>& b) {
                      return a.second < b.second;   // ascending by skill
                  });
}
```

one could also write the function `gameRound` with a for loop, even though the while is clearer here.

```cpp
void gameRound(vector<pair<string, double> >& participants) {
    if (participants.size() < 2) return;

    for (size_t idx = 0; idx < participants.size(); ++idx) {
        bernoulli_distribution hit(participants[nPlayer].second);
        if (!hit(rng)) 
            // missed shot
            continue;

        // Players shoot in order of skills (ascending).
        // Kill the most lethal (last) then second to last, etc.
        const size_t mostLethal = participants.size() - 1;
        const size_t target = (nPlayer == mostLethal) ? nPlayer - 1 : mostLethal;

        // most lethal is shot
        participants.erase(participants.begin() + target);

        // if we removed element before current shooter,
        // current shooter's index decreased by 1
        if (target < nPlayer) --nPlayer;

        if (participants.size() < 2) break;
    }
}


```