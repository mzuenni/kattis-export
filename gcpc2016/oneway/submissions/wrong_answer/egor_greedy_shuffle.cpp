#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::pair<size_t, size_t> Edge;
using namespace std;
/*
  version of egor_greedy which shuffles the edges and tries to rerun the algorithm on the new order
*/

int getBestD(size_t n, vector<Edge> &edges){
    size_t m=edges.size();
    vi taken(n,0);
    vi pot(n,0);
    for(size_t i=0;i<m;i++){
        pot[edges[i].first]++;
        pot[edges[i].second]++;
    }
    
    for(size_t step=0;step<m;step++){
      //find edge with minimal score
      size_t index=-1;
      int min=1000000000;
      for(size_t i=step;i<m;i++){
           size_t left=edges[i].first;
           size_t right=edges[i].second;
           int left_cost=2*taken[left]+pot[left];
           int right_cost=2*taken[right]+pot[right];
           //it is better to be free and to have a big difference to the partner
           int eval=std::min(left_cost, right_cost)*1000-abs(left_cost-right_cost); 
           if(eval<min){
                min=eval;
                index=i;
           }
      }
      std::swap(edges[step], edges[index]);
      
      size_t left=edges[step].first;
      size_t right=edges[step].second;
      //to the one with the smaller score:
      if(2*taken[left]+pot[left]<2*taken[right]+pot[right])
           taken[left]++;
      else
            taken[right]++;
      pot[left]--;
      pot[right]--;
   }
   
   return *std::max_element(taken.begin(), taken.end());
}

int main(){
    size_t n;
    size_t m;
    
    cin>>n>>m;
    vector<Edge> edges(m);
    for(size_t i=0;i<m;i++){
        std::cin>>edges[i].first>>edges[i].second;
        edges[i].first--;edges[i].second--;
   }
    
   //just try out 1000 different orders and take the best: 
   int minD=m;
   for(size_t i=0;i<200;i++){
      std::random_shuffle(edges.begin(), edges.end());
      minD=min(minD, getBestD(n, edges));
   }

   cout<<minD<<endl;
}


