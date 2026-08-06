#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX    500
#define STEP    35

int main() {
  int j,p,H,L;
  unsigned long long ntc = (MAX+STEP-1)/STEP;
 
  cout << (ntc*ntc*ntc*ntc) << endl;
  for (j = 1; j <= MAX; j+=STEP) {
  for (p = 1; p <= MAX; p+=STEP) {
  for (H = 1; H <= MAX; H+=STEP) {
  for (L = 1; L <= MAX; L+=STEP) {
    cout << j << " " << p << " " << H << " " << L << endl;
  }}}}
  return 0;
}
