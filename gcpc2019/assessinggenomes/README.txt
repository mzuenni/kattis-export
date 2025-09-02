This problem is an adaptation of two Stack Overflow questions ( https://stackoverflow.com/questions/54041397/ and https://stackoverflow.com/questions/55823298/ ) I encountered a while ago.
Essentially, it deals with the two following problems:

1)

  Given a string s, find the smallest substring u of s such that s = u^m for some m.

To efficiently solve this problem, two observations are of interest:

 1. A string consists of the same pattern repeated multiple times if and only if the string is a non-trivial rotation of itself.
 2. If x and y are strings of the same length, then x is a rotation of y if and only if x is a substring of yy.

Using these two properties, its easy to find this u.
Notably, the index of x in yy of 2. yields the string u.

2)

  We are given two float vectors a and b.
  We want to find a permutation of a and b, yielding a' and b', such that the euclidian distance between a' and b' is minimized (over all possible permutations)
  Formally, let a, b \in R^n and \Pi_n the set of all length-n permutations.
  Find

    min_{\pi_a, \pi_b \in \Pi_n} \sqrt(\sum_{i = 1}^n (a(\pi_a(i)) - b(\pi_b(i)))^2).

The key observation is that this permutation can easily be obtained by sorting the two vectors.
This can be proven by a simple proof of contradiction.
Sorting of course is significantly faster than any obvious, generic solution approach (brute force, minimum cost perfect matching, etc.).
