One gallon is 3785.41 milliliters. Write a program that will read the volume of
a package of milk in milliliters, and output the volume in gallons, as well as the
number of packets needed to yield at least one gallon of milk.

Important notes:
- Use a constant variable to store the conversion factor (ML_PER_GALLON).
- When calculating the number of packets, divide ML_PER_GALLON by the package volume.
- If the division result is not an integer, round up to the next whole number.
- If the division result is an integer (i.e., ML_PER_GALLON is exactly divisible by the package volume), do not add an extra packet.
- To implement this, store the division result in a temporary variable, cast it to int, and compare. If the division result is greater than its integer part, increment the packet count by 1.

Example:
If ML_PER_GALLON = 3785.41 and package volume = 1000 ml:
  division = 3785.41 / 1000 = 3.78541
  packets_needed = 4

If package volume = 3785.41 ml:
  division = 3785.41 / 3785.41 = 1.0
  packets_needed = 1
