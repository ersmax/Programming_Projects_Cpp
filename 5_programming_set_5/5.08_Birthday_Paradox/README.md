The birthday paradox is that there is a surprisingly high probability that two people
in the same room happen to share the same birthday. By birthday, we mean the same
day of the year (ignoring leap years), but not the exact birthday including the birth
year or time of day. Write a program that approximates the probability that two
people in the same room have the same birthday, for 2 to 50 people in the room.
The program should use simulation to approximate the answer. Over many trials
(say, 5000), randomly assign birthdays to everyone in the room. Count up the
number of times at least two people have the same birthday, and then divide by
the number of trials to get an estimated probability that two people share the same
birthday for a given room size.
Your output should look something like the following. It will not be exactly the
same due to the random numbers:
For 2 people, the probability of two birthdays is about 0.002
For 3 people, the probability of two birthdays is about 0.0082
For 4 people, the probability of two birthdays is about 0.0163
. . .
For 49 people, the probability of two birthdays is about 0.9654
For 50 people, the probability of two birthdays is about 0.969

---