//Author: Stefan Toman

//This is an easy submission to compute 8^n for large n.  It was written for
//a version of the problem with n <= 100.000 but should also work for n <=
//20 as it is now.  This submission is not optimized, in particular
//multiplying by bigger number or using repeated squaring would improve the
//speed.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  //read input
  int n;
  cin >> n;
  long long max = pow(10, 17);
  
  //compute 8^n
  vector<long long> r (1, 1);
  for(int i = 0; i < n; i++) {
    for(int j = r.size() - 1; j >= 0; j--) {
      r[j] *= 8;
      if(r[j] >= max) {
        if(j == r.size() - 1) {
          r.push_back(0);
        }
        int t = r[j]/max;
        r[j] -= t * max;
        r[j+1] += t;
      }
    }
  }
  
  //print answer
  cout << r[r.size() - 1];
  for(int j = r.size() - 2; j >= 0; j--) {
    cout << setfill('0') << setw(17) << r[j];
  }
  cout << endl;
  return 0;
}