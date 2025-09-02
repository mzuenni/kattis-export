Problem idea:
A multiplication was performed in a number system of unknown base; the two factors and the product are given.
What is a possible base?

Solution:
Implement own function for multiplication for a given base.
Binary search over systems (min occuring digit + 1) to (max base).
If result is greater than the given product in chosen system, correct system must be greater;
equivalent for smaller result.

Complexity:
n : number of digits in the factors
m : max possible system
Multiplication: O(d^2)
Total : O(log(m) * d^2)

Difficulty:
50

Alternative:
An addition instead of a multiplication is performed
-> Look for a digit position where the sum digit is smaller
than the theoretical sum of the digits
=> theoretical sum is greater than the base => base can be calculated
=> check if rest of the calculation works in this base

If at every digit position the sum digit is equal to the theoretical
sum digit, all bases > max occuring digit are valid.

=> Difficulty: 20
