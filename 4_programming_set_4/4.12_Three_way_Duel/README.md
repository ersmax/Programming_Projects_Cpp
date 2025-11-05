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

# My mathematical explanation of the Game Theory of Three-Way duel.

0. Turn order repeats A → B → C. 
   Everyone always aims at the most accurate opponent still alive.

| Shooter         | Accuracy       |
| --------------- | -------------- |
| **Aaron (A)**   | (p_A=\tfrac13) |
| **Bob (B)**     | (p_B=\tfrac12) |
| **Charlie (C)** | (p_C=1)        |

1. Two-person duel when Charlie is gone

| Situation | Who fires first       | Aaron’s win probability                                         |
| --------- | --------------------- | --------------------------------------------------------------- |
| A vs B    | **Aaron** fires first | (P_{AB}^{A}= \frac{1/3}{1-\frac23\cdot\frac12}= \tfrac12)       |
| A vs B    | **Bob** fires first   | (P_{AB}^{B}= (1-p_B),P_{AB}^{A}= \frac12\cdot\frac12= \tfrac14) |
| A vs C    | **Aaron** fires first | (P_{AC}=p_A = \tfrac13)                                         |

2. Strategy 1: Aaron shoots at Charlie first

| Path                                                                    | Probability of the path                         | Aaron’s eventual win prob. on that path |
| ----------------------------------------------------------------------- | ----------------------------------------------- | --------------------------------------- |
| **(1)** A hits C → duel A vs B, **Bob** to fire                         | (p_A=\tfrac13)                                  | (P_{AB}^{B}= \tfrac14)                  |
| **(2a)** A misses, B hits C → duel A vs B, **Aaron** to fire            | ((1-p_A)p_B=\tfrac23\cdot\tfrac12=\tfrac13)     | (P_{AB}^{A}= \tfrac12)                  |
| **(2b)** A misses, B misses, C kills B → duel A vs C, **Aaron** to fire | ((1-p_A)(1-p_B)=\tfrac23\cdot\tfrac12=\tfrac13) | (P_{AC}= \tfrac13)                      |

Adding the probabilities:

P = 1/3·1/4 + 1/3·1/2 + 1/3·1/3
= 1/12 + 1/6 + 1/9
= 3/36 + 6/36 + 4/36 = 13/36 ≈ 0.36111 = 36.11%

The simulation result 36.10% matches the analytical 36.11%.

3. Strategy 2: Aaron misses his first shot (until one participant dies)
    - Aaron first shoots into the air
    - Bob shoots at Charlie

| Branch     | Path probability | Resulting duel                        | Aaron’s chance in that duel |
| ---------- | ---------------- | ------------------------------------- | --------------------------- |
| B hits C   | (p_B=\tfrac12)   | A vs B, **Aaron** to fire             | (P_{AB}^{A}=\tfrac12)       |
| B misses C | (1-p_B=\tfrac12) | C kills B → A vs C, **Aaron** to fire | (P_{AC}= \tfrac13)          |


P_A_miss = (1/2)(1/2) + (1/2)(1/3) = 1/4 + 1/6 = 3/12 + 2/12 = 5/12 ≈ 0.4167 = 41.67%.
Simulation results ≈ 42.3% and 42.6% are within expected sampling error and agree with the analytical value.

4. The ground truth: Bob will never try to miss a shot at Charlie

If Bob declines his first shot, Charlie immediately kills him (Charlie never misses).
Bob’s winning probability would drop to 0 %.
Shooting at Charlie (his strongest rival) is strictly better for Bob, so the equilibrium of the game is:
- Aaron intentionally misses.
- Bob fires at Charlie.
- Charlie fires at Bob.

5. Theoretical results vs Empirical results

| Strategy profile                          | Aaron                        | Bob                         | Charlie                |
| ----------------------------------------- | ---------------------------- | --------------------------- | ---------------------- |
| **Normal play** – Aaron shoots at Charlie | (\frac{13}{36}\approx 36.1%) | (\frac{5}{12}\approx 41.7%) | (\frac29\approx 22.2%) |
| **Aaron misses first** (equilibrium)      | (\frac{5}{12}\approx 41.7%)  | (\frac14 = 25%)             | (\frac13\approx 33.3%) |

6. Final Observation

For Aaron, intentionally missing on his first shot is unequivocally better:

41.7% chance of winning versus 36.1% if he tries to hit Charlie right away.

The empirical result for 10,000 runs are consistent with these exact values, 
so the program runs just fine.

## Implementation



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