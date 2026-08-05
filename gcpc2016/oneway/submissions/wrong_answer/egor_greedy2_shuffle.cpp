#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::pair<size_t, size_t> Edge;
/*
  version of egor_greedy2 which shuffles the edges and tries to rerun the algorithm on the new order
*/

int estimate_max_d(const std::vector<Edge> &edges, int n){ 
    std::vector<int> cnts(n,0);
    for(const auto &edge:edges)
         if(cnts[edge.first]<cnts[edge.second])
             cnts[edge.first]++;
         else
             cnts[edge.second]++;
    
    return *std::max_element(cnts.begin(), cnts.end());
}

int estimate_best(std::vector<Edge> &edges, size_t n, int min){
   
   size_t m=edges.size();
   
   vi taken(n,0);
   vi pot(n,0);
    

   for(size_t i=0;i<m;i++){
        pot[edges[i].first]++;
        pot[edges[i].second]++;
   }
   
   //nodes takes all edges if its degree is less minimum
   size_t step=0;
   bool changed=true;
   while(changed){
        changed=false;
        for(size_t index=step;index<m;index++){
           if(pot[edges[index].first]<=min){
                 pot[edges[index].first]--;
                 pot[edges[index].second]--;
                 std::swap(edges[step], edges[index]);
                 step++;     
                 changed=true;
                 continue;    
           }
           if(pot[edges[index].second]<=min){
                 pot[edges[index].second]--;
                 pot[edges[index].first]--;
                 std::swap(edges[step], edges[index]);
                 step++;     
                 changed=true;
                 continue;    
           }
        }
   }
    
   for(;step<m;step++){
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
    
    std::cin>>n>>m;
    std::vector<Edge> edges(m);
    
    for(size_t i=0;i<m;i++){
        std::cin>>edges[i].first>>edges[i].second;
        edges[i].first--;edges[i].second--;
   }
   
   
   int bestD=m;
   for(size_t i=0;i<30;i++){ 
       std::random_shuffle(edges.begin(), edges.end());
      
       int lower=0;
       int upper=estimate_max_d(edges, n);
        
        while(lower+1<upper){
            int middle=(lower+upper)/2;
            int received=estimate_best(edges, n, middle);
            if(received<=middle)
                upper=middle;
            else
                lower=middle;
        }
        
        bestD=std::min(bestD, upper);
    }
    
    
    std::cout<<bestD<<"\n";

}


