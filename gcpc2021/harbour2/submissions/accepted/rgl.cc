#include <bits/stdc++.h>
using namespace std;

// TODO: it isn't clear whether the crane "transports a parcel away" every
//       single operation, or only after finding the $i$th parcel in the $i$th
//       iteration.
//
//       This solution assumes the latter.

int main(){
  int n,s1,s2; cin>>n>>s1>>s2;
  vector<int> l(n+1,-1),r(n+1,-1);

  vector<int> code(n+1); for (auto &i: code) cin>>i;
  reverse(code.begin()+s1,code.end());

  for (int i=0,p=-1; i<=n; i++){
    l[code[i]]=p; if (~p) r[p]=code[i];
    p=code[i];
  }

  int occur=(s1 and code[s1-1]==0 or s2 and code[n-s2+1]==0);

  for (int i=1; i<=n; i++){
    if (l[0]==i or r[0]==i) ++occur;
    if (~l[i]) r[l[i]]=r[i];
    if (~r[i]) l[r[i]]=l[i];
  }

  cout<<occur<<endl;
}
