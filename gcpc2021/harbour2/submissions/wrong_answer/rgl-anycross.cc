#include <bits/stdc++.h>
using namespace std;

// This solution misinterprets the problem statement as "find all of the
// times when item 0 is on top of a stack".
//
// Must be clear from the samples that this is not correct.

int main(){
  int n,s1,s2; cin>>n>>s1>>s2;

  vector<int> code(n+1); for (auto &i: code) cin>>i;
  reverse(code.begin()+s1,code.end());

  vector<int> x(n+1);
  for (int i=0; i<=n; i++){
    x[code[i]]=i;
  }

  int occur=(s1 and code[s1-1]==0 or s2 and code[n-s2+1]==0);

  for (int i=1; i<n; i++){
    if ((x[i]<x[0])!=(x[i+1]<x[0])) ++occur;
  }

  cout<<occur+1<<endl;
}
