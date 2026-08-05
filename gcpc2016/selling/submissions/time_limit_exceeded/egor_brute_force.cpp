/*

  this solution trys to brute force all possible configurations. 
    As optimization it uses
      1)a heuristic for the order in which the merchants are handled
      2)branching&prunning
*/

#include <bits/stdc++.h>

using namespace std;

size_t m;
size_t c;

typedef vector<int> vi;
typedef vector<vi> Table;
typedef pair<double, size_t> Element;
typedef vector<Element> Row;
typedef vector<Row> Candidates;

Table offers;
Table best_offers;
Candidates cands;
Row order;
    
int best=0;
void prune_and_branch(size_t merchant_index, size_t cpu_left, int money){
    if(merchant_index==m || cpu_left==0){
        best=max(best, money);
        return;
    }
    //check for early exit, prune by estimation of the best possible outcome:
    int max_can_add=0;
    for(size_t i=merchant_index;i<m;i++)       
        max_can_add+=best_offers[order[i].second][cpu_left-1];
        
    if(best>=money+max_can_add)
        return;
        
    //not pruned, so branch  
    size_t merchant=order[merchant_index].second;
    for(size_t i=0;i<c;i++){
        size_t cpu_sold=cands[merchant][i].second;
        if(cpu_sold<cpu_left)
            prune_and_branch(merchant_index+1, cpu_left-cpu_sold-1, money+offers[merchant][cpu_sold]);
    }
    //don't forget to just skip the current merchant:
    prune_and_branch(merchant_index+1, cpu_left, money); 
}

int main(){
	cin >> c >> m;
	offers.resize(m);
	best_offers.resize(m);
	cands.resize(m);
   
    
    for(size_t i=0;i<m;i++){
        for(size_t j=0;j<c;j++){
          int p; cin >> p;
          offers[i].push_back(p);
          best_offers[i].push_back(j==0 ? p : max(p, best_offers[i].back()));        
          cands[i].push_back(make_pair(-p/(j+1.0), j));
        }
        sort(cands[i].begin(), cands[i].end());
        order.push_back(make_pair(cands[i].front().first, i));
    }
    
    sort(order.begin(), order.end());

    
    prune_and_branch(0, c, 0);
    
    
    cout << best << endl;
}
