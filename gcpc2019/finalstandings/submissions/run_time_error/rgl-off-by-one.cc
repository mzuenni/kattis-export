#include <bits/stdc++.h>
using namespace std;

enum Problem: unsigned char{failed = 0, solved = 1, attempted = 2};

template <class S,class A,class D>
D get_distribution(S strength, A const &attempts, D const &difficulties){
  D prob(difficulties.size()+1);
  prob[0]=1.L;
  for (int i=0; i<attempts.size(); i++){
    auto chance_solve=strength*difficulties[i];
    if (attempts[i] != attempted) chance_solve=(attempts[i] == solved);
    for (int j=prob.size(); j--;)
      prob[j]=prob[j]*(1-chance_solve) + (j?prob[j-1]*chance_solve:0);
  }
  return prob;
}

int main(){
  int teams,problems; cin>>teams>>problems;

  vector<long double> strengths(teams-1), difficulties(problems);
  for (auto &i: strengths) cin>>i;
  for (auto &i: difficulties) cin>>i;

  vector<vector<Problem>> attempts(teams, vector<Problem>(problems));
  for (auto &i: attempts)
    for (auto &j: i)
      {string s; cin>>s; j=(s=="-"?failed:s=="X"?solved:attempted);}

  int solved=accumulate(attempts.back().begin(),attempts.back().end(),0);
  long double res=1.L;
  for (int i=0; i<teams /* BUG: should be teams-1 */; i++){
    auto const distrib=get_distribution(strengths[i], attempts[i], difficulties);
    res*=1.L-accumulate(distrib.begin()+solved+1,distrib.end(),0.L);
  }
  cout.precision(10);
  cout<<fixed<<res<<endl;
}
