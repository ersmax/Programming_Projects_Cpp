# Practical C++ Problems — Documentation Index

This repository contains practical, real-life programming problems solved in C++ std 14/20.
This README lists the documentation files for the collections: `Set 1` - `Set 5`
(much more to come related to OOP, memory management, pointers, etc. for a total of 20 sections). 
Check also my [Other projects](https://github.com/ersmax)

## Projects set 1

1. [Volume](1_programming_set_1/01_Volume) \- Convert milliliters to gallons and compute number of packets needed.
2. [Diet](1_programming_set_1/02_Diet) \- Estimate maximum safe diet soda consumption based on sweetener toxicity scaling.
3. [Sales_Profit_Increase](1_programming_set_1/03_Sales_Profit_Increase) \- Calculate sales and profit increases given previous year's figures.
4. [Loan](1_programming_set_1/04_Loan) \- Compute face value and monthly payment for a discount installment loan.
5. [Truck_capacity](1_programming_set_1/05_Truck_capacity) \- Determine if a truck is overloaded and how many boxes to add/remove.
6. [cab_fare](1_programming_set_1/06_cab_fare) \- Compute cab fare based on distance brackets and time charge.
7. [calories_deficit](1_programming_set_1/07_calories_deficit) \- Calculate calories burned during a staged treadmill workout.
8. [Babylonian_algorithm](1_programming_set_1/08_Babylonian_algorithm) \- Babylonian method to approximate square roots (5 iterations).
9. [arcade_prize](1_programming_set_1/09_arcade_prize) \- Redeem coupons for candy bars and gumballs with preference logic.
10. [Plane_distance](1_programming_set_1/10_Plance_distance) \- Compute airplane distance and convert speed to meters per second.
11. [Time](1_programming_set_1/11_Time) \- Convert total seconds into hours, minutes, and seconds.
12. [BMI](1_programming_set_1/12_BMI) \- Estimate ideal body weight based on height (5 feet baseline + 5 lb per inch).
13. [Coffee_intake](1_programming_set_1/13_Coffee_intake) \- Compute how many drinks reach a lethal caffeine dose estimate.

---

## Projects set 2

1. [Apartment_price](2_programming_set_2/2.01_Apartment_price) \- Estimate apartment prices per floor including compound base price increases, amenities, and taxes.
2. [Interests_deposit](2_programming_set_2/2.02_Interests_deposit) \- Calculate how many months a deposit lasts with monthly withdrawals and interest; includes boundary checks.
3. [Financing_education](2_programming_set_2/2.03_Financing_education) \- Determine how many children a donor can sponsor and remaining amount.
4. [Prime_numbers](2_programming_set_2/2.04_Prime_numbers) \- Print all prime numbers between 3 and 100 using an efficient divisor check.
5. [Cryptarithmetic_puzzle](2_programming_set_2/2.05_Cryptarithmetic_puzzle) \- Solve TOO + TOO + TOO + TOO = GOOD by brute-force digit assignment with uniqueness checks.
6. [Buoyancy](2_programming_set_2/2.06_Buoyancy) \- Determine if a sphere floats or sinks in water using Archimedes' principle and sphere volume formula.
7. [GPA](2_programming_set_2/2.07_GPA) \- Compute grade point average from letter grades with validation and case-insensitive input handling.
8. [Equivalent_Temperatures](2_programming_set_2/2.08_Equivalent_Temperatures) \- Find the integer temperature that is the same in Celsius and Fahrenheit.
9. [Babylonian_cyclic](2_programming_set_2/2.09_Babylonian_cyclic) \- Babylonian algorithm to compute square root iteratively until within 1% of previous guess.
10. [Text_replacement](2_programming_set_2/2.10_Text_replacement) \- Read a text file and replace occurrences of hate with love while printing words.
11. [Ideal_BMI](2_programming_set_2/2.11_Ideal_BMI) \- Read names and heights from a file and compute ideal body weight for each entry.
12. [Benfords_Law](2_programming_set_2/2.12_Benfords_Law) \- Analyze leading-digit distribution of numbers from a file to test Benford's Law.
13. [Pair_sum](2_programming_set_2/2.13_Pair_sum) \- Check whether any pair from a file of 10 integers sums to a user-provided target.

---

## Projects set 3

1. [File_size](3_programming_set_3/3.01_File_size) \- Compute video file size from bit rate and duration (megabyte = 8000 kilobits).
2. [Salary_hike](3_programming_set_3/3.02_Salary_hike) \- Compute employee raise percentage and allow repeated calculations.
3. [Future_salary_hike](3_programming_set_3/3.03_Future_salary_hike) \- Estimate future salaries and total future salary over N years.
4. [Gravitational_force](3_programming_set_3/3.04_Gravitational_force) \- Compute gravitational force using global constant G.
5. [Clothing_size](3_programming_set_3/3.05_Clothing_size) \- Compute hat, jacket, and waist sizes with age adjustments.
6. [Scores_statistics](3_programming_set_3/3.06_Scores_statistics) \- Compute average and standard deviation of four scores.
7. [Euclidean_distance](3_programming_set_3/3.07_Euclidean_distance) \- Compute distance between two points using the Euclidean formula.
8. [Bottles_beer](3_programming_set_3/3.08_Bottles_beer) \- Print the Ninety-Nine Bottles of Beer song using words for numbers.
9. [Game_of_craps](3_programming_set_3/3.09_Game_of_craps) \- Simulate 10,000 games of craps (Pass Line) and compute the winning probability.
10. [Estimated height](3_programming_set_3/3.10_Estimated_height) \- Estimate the height of a child based on parents' heights and gender.
11. [Game_of_Pig](3_programming_set_3/3.11_Game_of_Pig) \- Two-player Pig game (human vs computer) based on turn-based die rolls.

    ![Game of Pig](3_programming_set_3/3.11_Game_of_Pig/GameOfPig.PNG)

12. [Day_from_date](3_programming_set_3/3.12_Day_from_date) \- Input a date (e\.g\., July 4 2008) 
    and output the corresponding day of the week using a table\-based algorithm 
    \([Wikipedia: Calculating the day of the week](http://en.wikipedia.org/wiki/Calculating_the_day_of_the_week)\)\. 
    Includes both map\-based and switch\-based implementations for month value lookup\.
13. [Price_Winners_Lottery](3_programming_set_3/3.13_Price_Winners_Lottery) 
    \- Randomly select Unique winners from Lottery finalists for identical prizes.  
    Uses the independent rule of selection without replacement.
    Includes two solution approaches: swap-and-shrink pool and boolean flag array to ensure no duplicate winners.
14. [Babylonian_square_root](3_programming_set_3/3.14_Babylonian_square_root) 
    \- Compute the square root of a positive number using the Babylonian algorithm until convergence within 
    1% of the previous guess. Use functions and input validation with several numbers, including error handling 
    for negative inputs.
15. [Likelihood of Death](3_programming_set_3/3.15_Likelihood_death) 
    \- Simulate the age at which a person will die in the USA using an Actuarial Life table provided by 
    the Social Security Administration for the 2025. 
    Input: starting `age` and `gender` (`M`/`F`). Output: simulated age of death (stops at `MAX_AGE` = 120). 
    [Data File](3_programming_set_3/3.15_Likelihood_death/likelihood_death_2025.txt) available at
    the [Social Security Administration website](https://www.ssa.gov/OACT/STATS/table4c6.html).

---

## Projects set 4

1. [Hour Conversion](4_programming_set_4/4.01_Hour_Conversion) 
   \- Convert 12-hour time format to 24-hour format with input validation.
   Check preconditions and proper input format (e.g., "02:30 PM") and insertion.
2. [Area Circumference](4_programming_set_4/4.02_Area_Circumference) 
   \- Calculate area and circumference of a circle given its radius.
   Validate that the radius is a positive number before performing calculations.
3. [Redeem Voucher](4_programming_set_4/4.03_Redeem_Voucher) 
   \- Redeem a voucher code for a discount on a purchase.
   Validate the voucher code against a predefined list and ensure the purchase amount is positive.
   Coded sorting and searching algorithms for voucher codes as well as input validation with `vector<pair>`.
4. [Feet Inches to Meters](4_programming_set_4/4.04_Feet_Inches_to_Meters) 
   \- Convert lengths between different units (e.g., inches to centimeters).
   Validate that the input length is a non-negative number and that the specified units are supported.
5. [Meters to Feet Inches](4_programming_set_4/4.05_Meters_to_Feet_Inches) 
   \- Convert lengths from meters and centimeters to feet and inches.
   Validate that meters are in [0, 2] and centimeters in [0, 99], truncating results to avoid rounding up.
6. [Length Conversion](4_programming_set_4/4.06_Length_Conversion) 
   \- Combine conversions between feet\+inches and meters\+centimeters.
   Present a menu for conversion direction, validate inputs, and allow repeated conversions until exit.
   Add structures for Feet/Inches and Meters/cm to handle properly function overloading and modularity.
7. [Pounds Ounces to Grams](4_programming_set_4/4.07_Pounds_Ounces_to_Grams) 
   \- Convert weights from pounds and ounces to kilograms and grams, allowing repeated conversions until exit.
8. [Grams to Pounds Ounces](4_programming_set_4/4.08_Grams_to_Pounds_Ounces) 
   \- Convert weights from grams to pounds and ounces, allowing repeated conversions until exit.
9. [Weight Conversion](4_programming_set_4/4.09_Weight_Conversion) 
   \- Combine conversions between pounds\+ounces and kilograms\+grams.
   Present a menu for conversion direction, validate inputs, and allow repeated conversions until exit.
   Add structures for Pounds/Ounces and Kilograms/Grams to handle properly function overloading and modularity.
10. [Length and Weight Conversion](4_programming_set_4/4.10_Length_Weight_Conversion) 
    \- Combine length and weight conversions into a single program with a menu and sub-menu, according to 
    the user's choice.
    Allow users to choose between length and weight conversions, validate inputs, and repeat until exit.
    Used function overloading, pass by reference and constant reference parameters. 
11. [Monty Hall Problem](./4_programming_set_4/4.11_Monty_Hall_Problem)
    \- Simulate a generalized Monty Hall experiment to compare empirical win rates for the two strategies: staying with the initial pick versus switching after the host reveals losing doors.  
    - Configurable parameters: number of doors (`DOORS`) and number of simulations (`GAMES`) so you can test small and large-scale scenarios (e.g., `DOORS = 100`, `GAMES = 10000`).  
    - Supports the canonical host rule (host opens `n-2` losing doors, leaving exactly one other) and easily adapts to variants where the host leaves multiple unopened doors.  
    - Written in modern C++ using `std::vector`, iterators, `std::mt19937` and `std::uniform_int_distribution` for unbiased draws and reproducible results (seedable).  
    - Output: counts and percentages for wins when staying vs. switching; optional verbose mode for single-run tracing.  
    - Empirical results: For 10,000 runs and 100 doors, the simulation converges to 60% probability of success.
        <p align="center">
            <img src="4_programming_set_4/4.11_Monty_Hall_Problem/Figures/MontyHall.PNG" alt="Monty Hall diagram" width="48%" />
            <img src="4_programming_set_4/4.11_Monty_Hall_Problem/Figures/MontyHall10000.PNG" alt="Monty Hall" width="48%" />
        </p>
12. [Three Way Duel](./4_programming_set_4/4.12_Three_Way_Duel)
    \- Simulate a three-way duel (truel) between three marksmen with different accuracies, under different strategies 
       (aiming at the strongest opponent, intentionally missing).
    - Written in modern C++ using `std::vector`, RNG`std::mt19937`, `bernoulli_distribution`.
    - The theory suggests 36.1% and 41.7% chances of success under 2 strategies. These results are validated through simulation.
        <p align="center">
            <img src="4_programming_set_4/4.12_Three_Way_Duel/Figures/EmpiricalResults.png" alt="Three Way Duel diagram" width="48%" />
        </p>
13. [Treadmill Pace](./4_programming_set_4/4.13_Treadmill_Pace)
    \- Convert a running pace and speed with input validation to demonstrates overloaded functions.
14. [Time Difference](./4_programming_set_4/4.14_Time_Difference)
    \- Compute the number of minutes to advance a time\-machine from a start time to an end time using 24\-hour HHMM notation. 
      Input validation to ensure times are in the range 0000 to 2359 and minutes are valid (00 to 59).
15. [Convert Lowest Terms](./4_programming_set_4/4.15_Convert_Lowest_Terms)
    \- Convert a fraction to its lowest terms using the greatest common divisor (GCD) algorithms, that is Prime factorization and Euclidean algorithm.
      Input validation to ensure denominator is not zero and both numerator and denominator are integers.
16. [Highest Score](./4_programming_set_4/4.16_Highest_Score)
    \- Read names and scores from a file, determine the highest score, and print the highest score and relative name.
      Input validation to ensure scores are non-negative integers and handle file reading errors.
17. [Get Player score and avg comparison](./4_programming_set_4/4.17_Get_Score_Average_Score)
    \- Read player names and scores from a file, query the score of a player and compare it with the average.
      Input validation to handle file reading errors.
18. [Sorting Quicksort](./4_programming_set_4/4.18_Sorting_Trivial_Quick_Merge)
    \- Implement the Quicksort algorithm (by reference and by value or copy) to sort an array of integers and apply Hoare's algorithm.

---

## Project Set 5

1. [Car Mileage Visualization](5_programming_set_5/5.01_Graph_Car_Mileage)
   \- Compare a car's average mileage at different speeds with actual mileage values, and prints 
      a formatted comparison table and an ASCII graph.
   <p align="center">
     <img src="5_programming_set_5/5.01_Graph_Car_Mileage/Figures/mileageTable.PNG" alt="car mileage table" width="48%" />
     <img src="5_programming_set_5/5.01_Graph_Car_Mileage/Figures/mileageGraph.PNG" alt="car mileage graph" width="48%" />
   </p>    


2. [...]