// Author: Stefan Pszczolkowski
// Expected Result: Correct
// Problem C: Candy Distribution
// @EXPECTED_RESULTS@: CORRECT

#include <stdio.h>
#include <stdlib.h>

//Extended euclidean algorithm. It returns the gtreatest common divisor of a and b 
//and the coefficients that satisfy Bézout's identity
int* ext_euclid(int a, int b) {
  int *ans;
  int q, temp;
  
  ans = (int *) malloc(3 * sizeof(int));

  if (b == 0)  { 
    ans[0] = a;
    ans[1] = 1;
    ans[2] = 0;
  } else {
    q = a/b;
    ans = ext_euclid(b, a % b);
    temp = ans[1] - ans[2]*q;
    ans[1] = ans[2];
    ans[2] = temp;
  }

  return ans;
}

int solve(int k, int c) { 
  int *ans;
  
  //trivial solution
  if (c == 1)
    return k+1;
  
  ans = ext_euclid(k, c);
  
  //if GCD is 1 (K and C are coprime) ---> solution exists, find the positive one
  if (ans[0] == 1) {
    while (ans[2] <= 0)
      ans[2] += k;
    
    return ans[2];
  }
  
  //GCD is not 1 (K and C are not coprime) ---> no solution
  return -1;
}
  

int main(int argc, char **argv) {
  int tests, t;
  int k,c,sol;
  
  scanf("%d\n",&tests);
  
  for (t = 0; t < tests; t++) {
    scanf("%d %d\n",&k, &c);
    sol = solve(k, c);
    if (sol == -1)
      printf("IMPOSSIBLE\n");
    else
      printf("%d\n", sol);
  }
  return 0;
}
