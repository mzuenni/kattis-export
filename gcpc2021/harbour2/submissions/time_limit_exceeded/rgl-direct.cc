#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  int n,s0,s1; cin>>n>>s0>>s1;
  stack<int> l,r;
  vector<int> which(n+1);

  for (int i=0; i<s0; i++) {int x; cin>>x; which[x]=0; l.push(x);}
  for (int i=0; i<s1; i++) {int x; cin>>x; which[x]=1; r.push(x);}

  int score=0;
  auto update=[&](){
    if (not l.empty() and not l.top()) ++score;
    if (not r.empty() and not r.top()) ++score;
  };
  update();
  for (int i=1; i<=n; i++){
    int w=which[i];
    if (w==0){
      while (l.top()!=i) which[l.top()]=1, r.push(l.top()), l.pop();
      l.pop();
    }else{
      while (r.top()!=i) which[r.top()]=0, l.push(r.top()), r.pop();
      r.pop();
    }
    update();
  }

  cout<<score<<endl;
}
