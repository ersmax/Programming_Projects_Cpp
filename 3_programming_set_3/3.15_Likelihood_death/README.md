

---

README content for `3_programming_set_3/3.15_Likelihood_death/README.md`:

```markdown
# Likelihood of Death Simulator

## Overview
- Small C++ program that simulates the age at which a person will die using an actuarial life table.
- Input: starting `age` and `gender` (`M`/`F`).
- Output: simulated age of death (simulation ends at `MAX_AGE` = 120).

## Files
- `3_programming_set_3/3.15_Likelihood_death/15_Likelihood_death.cpp` — main implementation.
- `3_programming_set_3/3.15_Likelihood_death/likelihood_death_2025.txt` — cleaned data used by the program.
- `3_programming_set_3/3.15_Likelihood_death/README.md` — this file.

## Data source
- Source figures: Social Security Administration table, 2025: https://www.ssa.gov/OACT/STATS/table4c6.html
- The file `likelihood_death_2025.txt` was collected and cleaned locally for this project 
  (the in-code header text referencing 2009 is outdated).

## Build & run
- Open the project in CLion (Windows).
- Run or debug `15_Likelihood_death.cpp` from the IDE.
- Alternatively, compile with a C++17-capable compiler:
  - `g++ -std=c++17 15_Likelihood_death.cpp -o likelihood_sim`
  - `.\likelihood_sim`

## Design notes and function choices

- Reads the life-table file row-by-row and stores male/female death probabilities in two `std::vector<double>` indexed by age.
- Robustness choices:
  - Skips empty or malformed lines.
  - Uses `try`/`catch` around `stoi`/`stod` to avoid crashes on bad fields; invalid numeric fields default to `0.0`.
  - Resizes the vectors as needed so that `male[age]` / `female[age]` are valid.
- This approach favors a single in-memory load so repeated simulations are fast.


## Algorithm
  - Clamp input `age` to `[0, MAX_AGE]`.
  - For each year from the given age up to `MAX_AGE`, draw a uniform random number in \[0,1) 
    and compare it to the death probability for that year and gender.
  - If the random value is <= death probability for that year, return the current age (the person dies during that year).
  - If no death occurs by `MAX_AGE`, return `MAX_AGE`.

## Limitation: RNG choices
  - The program should seed the PRNG once in `main` and use it during simulation 
    to avoid repeated reseeding and global state issues.
  - However, as a simplification, the code uses `rand()` / `srand()` which is simpler 
    but has limitations (small `RAND_MAX`, global state, non-thread-safe, poorer statistical quality). 
    Prefer the C++11 `<random>` (e.g., `std::mt19937` + `std::uniform_real_distribution`) for production.

## A Nice addition: commaRemoval function
- Present in the code as a helper that removes commas from a string.
- Not required for the current `likelihood_death_2025.txt` format (space-separated, already cleaned).
- Kept intentionally for re-use on other fields or alternative data files that may include thousands-separators 
  or comma-containing fields (for example: life expectancy values, number-of-lives columns, or CSV variants). 
  It is a small, safe utility and may be useful if the data source format changes.

## Notes and Suggestions
- The simulation is stochastic: results differ each run unless a fixed RNG seed is used.
- If you prefer reproducible runs for testing, use a fixed seed (e.g., `std::mt19937 rng(12345);`) 
  instead of `std::random_device`.
- The code currently defaults malformed probabilities to `0.0`; 
  change this behavior if you prefer to fail fast or log warnings.

## License / attribution
- Data source: Social Security Administration (link above). 
  The cleaned file in this repository was prepared locally for this project.
  
## Table with data:

# Period Life Table, 2022 (as used in the 2025 Trustees Report)

| Exact age | Male Death probability a | Number of lives b | Life expectancy | Female Death probability a | Number of lives b | Life expectancy |
|---:|---:|---:|---:|---:|---:|---:|
| 0 | 0.006064 | 100,000 | 74.74 | 0.005119 | 100,000 | 80.18 |
| 1 | 0.000491 | 99,394 | 74.20 | 0.000398 | 99,488 | 79.60 |
| 2 | 0.000309 | 99,345 | 73.23 | 0.000240 | 99,449 | 78.63 |
| 3 | 0.000248 | 99,314 | 72.25 | 0.000198 | 99,425 | 77.65 |
| 4 | 0.000199 | 99,290 | 71.27 | 0.000160 | 99,405 | 76.66 |
| 5 | 0.000167 | 99,270 | 70.29 | 0.000134 | 99,389 | 75.67 |
| 6 | 0.000143 | 99,253 | 69.30 | 0.000118 | 99,376 | 74.68 |
| 7 | 0.000126 | 99,239 | 68.31 | 0.000109 | 99,364 | 73.69 |
| 8 | 0.000121 | 99,226 | 67.32 | 0.000106 | 99,353 | 72.70 |
| 9 | 0.000121 | 99,214 | 66.32 | 0.000106 | 99,343 | 71.71 |
| 10 | 0.000127 | 99,202 | 65.33 | 0.000111 | 99,332 | 70.72 |
| 11 | 0.000143 | 99,190 | 64.34 | 0.000121 | 99,321 | 69.72 |
| 12 | 0.000171 | 99,176 | 63.35 | 0.000140 | 99,309 | 68.73 |
| 13 | 0.000227 | 99,159 | 62.36 | 0.000162 | 99,295 | 67.74 |
| 14 | 0.000320 | 99,136 | 61.37 | 0.000188 | 99,279 | 66.75 |
| 15 | 0.000451 | 99,104 | 60.39 | 0.000224 | 99,260 | 65.76 |
| 16 | 0.000622 | 99,060 | 59.42 | 0.000276 | 99,238 | 64.78 |
| 17 | 0.000826 | 98,998 | 58.46 | 0.000337 | 99,211 | 63.80 |
| 18 | 0.001026 | 98,916 | 57.50 | 0.000395 | 99,177 | 62.82 |
| 19 | 0.001182 | 98,815 | 56.56 | 0.000450 | 99,138 | 61.84 |
| 20 | 0.001301 | 98,698 | 55.63 | 0.000496 | 99,094 | 60.87 |
| 21 | 0.001404 | 98,570 | 54.70 | 0.000532 | 99,044 | 59.90 |
| 22 | 0.001498 | 98,431 | 53.78 | 0.000567 | 98,992 | 58.93 |
| 23 | 0.001586 | 98,284 | 52.86 | 0.000610 | 98,936 | 57.97 |
| 24 | 0.001679 | 98,128 | 51.94 | 0.000650 | 98,875 | 57.00 |
| 25 | 0.001776 | 97,963 | 51.03 | 0.000699 | 98,811 | 56.04 |
| 26 | 0.001881 | 97,789 | 50.12 | 0.000743 | 98,742 | 55.08 |
| 27 | 0.001985 | 97,605 | 49.21 | 0.000796 | 98,669 | 54.12 |
| 28 | 0.002095 | 97,412 | 48.31 | 0.000855 | 98,590 | 53.16 |
| 29 | 0.002219 | 97,208 | 47.41 | 0.000924 | 98,506 | 52.20 |
| 30 | 0.002332 | 96,992 | 46.51 | 0.000988 | 98,415 | 51.25 |
| 31 | 0.002445 | 96,766 | 45.62 | 0.001053 | 98,318 | 50.30 |
| 32 | 0.002562 | 96,529 | 44.73 | 0.001123 | 98,214 | 49.35 |
| 33 | 0.002653 | 96,282 | 43.84 | 0.001198 | 98,104 | 48.41 |
| 34 | 0.002716 | 96,026 | 42.96 | 0.001263 | 97,986 | 47.47 |
| 35 | 0.002791 | 95,765 | 42.08 | 0.001324 | 97,863 | 46.53 |
| 36 | 0.002894 | 95,498 | 41.19 | 0.001403 | 97,733 | 45.59 |
| 37 | 0.002994 | 95,222 | 40.31 | 0.001493 | 97,596 | 44.65 |
| 38 | 0.003091 | 94,937 | 39.43 | 0.001596 | 97,450 | 43.72 |
| 39 | 0.003217 | 94,643 | 38.55 | 0.001700 | 97,295 | 42.79 |
| 40 | 0.003353 | 94,339 | 37.67 | 0.001803 | 97,129 | 41.86 |
| 41 | 0.003499 | 94,022 | 36.80 | 0.001905 | 96,954 | 40.93 |
| 42 | 0.003642 | 93,693 | 35.93 | 0.002009 | 96,769 | 40.01 |
| 43 | 0.003811 | 93,352 | 35.05 | 0.002116 | 96,575 | 39.09 |
| 44 | 0.003996 | 92,997 | 34.19 | 0.002223 | 96,371 | 38.17 |
| 45 | 0.004175 | 92,625 | 33.32 | 0.002352 | 96,156 | 37.25 |
| 46 | 0.004388 | 92,238 | 32.46 | 0.002516 | 95,930 | 36.34 |
| 47 | 0.004666 | 91,833 | 31.60 | 0.002712 | 95,689 | 35.43 |
| 48 | 0.004973 | 91,405 | 30.75 | 0.002936 | 95,429 | 34.53 |
| 49 | 0.005305 | 90,950 | 29.90 | 0.003177 | 95,149 | 33.63 |
| 50 | 0.005666 | 90,468 | 29.05 | 0.003407 | 94,847 | 32.73 |
| 51 | 0.006069 | 89,955 | 28.22 | 0.003642 | 94,524 | 31.84 |
| 52 | 0.006539 | 89,409 | 27.39 | 0.003917 | 94,180 | 30.96 |
| 53 | 0.007073 | 88,825 | 26.56 | 0.004238 | 93,811 | 30.08 |
| 54 | 0.007675 | 88,196 | 25.75 | 0.004619 | 93,413 | 29.20 |
| 55 | 0.008348 | 87,520 | 24.94 | 0.005040 | 92,982 | 28.34 |
| 56 | 0.009051 | 86,789 | 24.15 | 0.005493 | 92,513 | 27.48 |
| 57 | 0.009822 | 86,003 | 23.37 | 0.005987 | 92,005 | 26.63 |
| 58 | 0.010669 | 85,159 | 22.59 | 0.006509 | 91,454 | 25.78 |
| 59 | 0.011548 | 84,250 | 21.83 | 0.007067 | 90,859 | 24.95 |
| 60 | 0.012458 | 83,277 | 21.08 | 0.007658 | 90,217 | 24.12 |
| 61 | 0.013403 | 82,240 | 20.34 | 0.008305 | 89,526 | 23.31 |
| 62 | 0.014450 | 81,138 | 19.61 | 0.008991 | 88,782 | 22.50 |
| 63 | 0.015571 | 79,965 | 18.89 | 0.009681 | 87,984 | 21.70 |
| 64 | 0.016737 | 78,720 | 18.18 | 0.010343 | 87,132 | 20.90 |
| 65 | 0.017897 | 77,402 | 17.48 | 0.011018 | 86,231 | 20.12 |
| 66 | 0.019017 | 76,017 | 16.79 | 0.011743 | 85,281 | 19.34 |
| 67 | 0.020213 | 74,572 | 16.11 | 0.012532 | 84,279 | 18.56 |
| 68 | 0.021569 | 73,064 | 15.43 | 0.013512 | 83,223 | 17.79 |
| 69 | 0.023088 | 71,488 | 14.76 | 0.014684 | 82,099 | 17.03 |
| 70 | 0.024828 | 69,838 | 14.09 | 0.016025 | 80,893 | 16.27 |
| 71 | 0.026705 | 68,104 | 13.44 | 0.017468 | 79,597 | 15.53 |
| 72 | 0.028761 | 66,285 | 12.80 | 0.019195 | 78,206 | 14.80 |
| 73 | 0.031116 | 64,379 | 12.16 | 0.021195 | 76,705 | 14.08 |
| 74 | 0.033861 | 62,376 | 11.53 | 0.023452 | 75,079 | 13.37 |
| 75 | 0.037088 | 60,263 | 10.92 | 0.025980 | 73,319 | 12.68 |
| 76 | 0.041126 | 58,028 | 10.32 | 0.029153 | 71,414 | 12.00 |
| 77 | 0.045241 | 55,642 | 9.74 | 0.032394 | 69,332 | 11.35 |
| 78 | 0.049793 | 53,125 | 9.18 | 0.035888 | 67,086 | 10.71 |
| 79 | 0.054768 | 50,479 | 8.64 | 0.039676 | 64,678 | 10.09 |
| 80 | 0.060660 | 47,715 | 8.11 | 0.044156 | 62,112 | 9.49 |
| 81 | 0.067027 | 44,820 | 7.60 | 0.049087 | 59,370 | 8.90 |
| 82 | 0.073999 | 41,816 | 7.11 | 0.054635 | 56,455 | 8.34 |
| 83 | 0.081737 | 38,722 | 6.64 | 0.061066 | 53,371 | 7.79 |
| 84 | 0.090458 | 35,557 | 6.18 | 0.068431 | 50,112 | 7.26 |
| 85 | 0.100525 | 32,340 | 5.75 | 0.076841 | 46,683 | 6.76 |
| 86 | 0.111793 | 29,089 | 5.34 | 0.086205 | 43,095 | 6.28 |
| 87 | 0.124494 | 25,837 | 4.94 | 0.096851 | 39,380 | 5.83 |
| 88 | 0.138398 | 22,621 | 4.58 | 0.109019 | 35,566 | 5.40 |
| 89 | 0.153207 | 19,490 | 4.23 | 0.121867 | 31,689 | 5.00 |
| 90 | 0.169704 | 16,504 | 3.91 | 0.135805 | 27,827 | 4.62 |
| 91 | 0.187963 | 13,703 | 3.60 | 0.151108 | 24,048 | 4.27 |
| 92 | 0.208395 | 11,128 | 3.32 | 0.168020 | 20,414 | 3.94 |
| 93 | 0.230808 | 8,809 | 3.06 | 0.186340 | 16,984 | 3.64 |
| 94 | 0.253914 | 6,776 | 2.83 | 0.206432 | 13,819 | 3.36 |
| 95 | 0.277402 | 5,055 | 2.63 | 0.228086 | 10,967 | 3.10 |
| 96 | 0.300882 | 3,653 | 2.44 | 0.250406 | 8,465 | 2.87 |
| 97 | 0.324326 | 2,554 | 2.28 | 0.273699 | 6,346 | 2.66 |
| 98 | 0.347332 | 1,726 | 2.13 | 0.296984 | 4,609 | 2.47 |
| 99 | 0.369430 | 1,126 | 2.00 | 0.319502 | 3,240 | 2.30 |
| 100 | 0.391927 | 710 | 1.88 | 0.342716 | 2,205 | 2.14 |
| 101 | 0.414726 | 432 | 1.76 | 0.366532 | 1,449 | 2.00 |
| 102 | 0.437722 | 253 | 1.66 | 0.390844 | 918 | 1.87 |
| 103 | 0.460800 | 142 | 1.56 | 0.415531 | 559 | 1.75 |
| 104 | 0.483840 | 77 | 1.47 | 0.440463 | 327 | 1.63 |
| 105 | 0.508032 | 40 | 1.39 | 0.466891 | 183 | 1.52 |
| 106 | 0.533434 | 19 | 1.31 | 0.494904 | 97 | 1.42 |
| 107 | 0.560105 | 9 | 1.23 | 0.524599 | 49 | 1.32 |
| 108 | 0.588111 | 4 | 1.15 | 0.556075 | 23 | 1.23 |
| 109 | 0.617516 | 2 | 1.08 | 0.589439 | 10 | 1.14 |
| 110 | 0.648392 | 1 | 1.01 | 0.624805 | 4 | 1.05 |
| 111 | 0.680812 | 0 | 0.94 | 0.662294 | 2 | 0.97 |
| 112 | 0.714852 | 0 | 0.87 | 0.702031 | 1 | 0.89 |
| 113 | 0.750595 | 0 | 0.81 | 0.744153 | 0 | 0.82 |
| 114 | 0.788125 | 0 | 0.75 | 0.788125 | 0 | 0.75 |
| 115 | 0.827531 | 0 | 0.70 | 0.827531 | 0 | 0.70 |
| 116 | 0.868907 | 0 | 0.64 | 0.868907 | 0 | 0.64 |
| 117 | 0.912353 | 0 | 0.59 | 0.912353 | 0 | 0.59 |
| 118 | 0.957970 | 0 | 0.54 | 0.957970 | 0 | 0.54 |
| 119 | 1.000000 | 0 | 0.50 | 1.000000 | 0 | 0.50 |

a \- Probability of dying within one year.  
b \- Number of survivors out of 100,000 born alive.

Note: The period life expectancy at a given age for 2022 is the average remaining number of years expected prior to death for a person at that exact age, born on January 1, using the mortality rates for 2022 over the course of his or her remaining life.

Data source: Social Security Administration table (2022 period life table) — https://www.ssa.gov/OACT/STATS/table4c6.html

Data preparation: The data in this table was collected and cleaned locally for this project.


```