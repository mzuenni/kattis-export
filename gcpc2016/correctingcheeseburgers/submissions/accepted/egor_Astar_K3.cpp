/* uses A* algorithm 

   every node gets a potential - the number of indices with v_i+1-v_i!=1
   every edge (v,w) gets value K+pot(w)-pot(v)
   
   K should be >= 5 because otherwise there could be negative edges, which is not guaranteed to work with dijkstra
   
   however K=3 seems to work (K==2 doesn't)
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

const int K=3;

typedef long long int Type;
typedef int  Info;
typedef std::unordered_map<Type, Info> Map;
typedef std::vector<Type> Vector;


Type goals[10]={0, 1, 12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789};

void decode(Type id, size_t N, Vector &res){
    for(size_t i=0;i<N;i++){
        res[N-i-1]=id%10;
        id/=10;
    }
}


Type bit_shuffle(const Vector &orig, size_t first, size_t second, size_t third){
    Type res=0;                 
    for(size_t i=second;i<third;i++)
        res=res*10+orig[i];
    for(size_t i=0;i<first;i++)
        res=res*10+orig[i];         
    for(size_t i=third;i<orig.size();i++)
        res=res*10+orig[i];      
    for(size_t i=first;i<second;i++)
        res=res*10+orig[i];
        
    return res;
}

int getGoodness(Type id, size_t N){
    int res=0;
    int last=N+1;
    for(size_t i=0;i<N;i++){
        Type z=id%10;
        if(z+1!=last)
            res++;
        last=z;
        id/=10;
    }
    if(last!=1)
      res++;
    return res;
}


int getDist(Type start, size_t N){

    Type goal=goals[N-1];
    if(goal==start) 
        return 0;
        
    Map dist;//first=dist, second=origin 
    typedef std::pair<Info, Type> State;
    std::priority_queue<State, std::vector<State>, std::greater<State> > q;
    
    dist[start]=getGoodness(start,N);
    q.push(std::make_pair(dist[start],start));
     
    
    
    while (!q.empty()){
        State state=q.top();
        q.pop();
        Info cur_dist=state.first;
        Type cur_id=state.second;
        if(cur_dist!=dist[cur_id])
          continue;
        Vector orig(N);
        decode(cur_id, N, orig);
        int old_potential=getGoodness(cur_id, N);
        //std::cout<<"current: "<<cur_id<<"dist="<<cur_dist<<" with potential "<<old_potential<<"\n";
        //brute force all possibilities
        for(size_t i=0;i<=N;i++)
            for(size_t j=i;j<=N;j++)
                for(size_t k=j;k<=N;k++){
                  Type next_id= bit_shuffle(orig,i,j,k);
                  int edge_cost=getGoodness(next_id,N)-old_potential+K;
                  int next_dist=cur_dist+edge_cost;
                  //std::cout<<" evaluating "<<next_id<<" edge_cost="<<edge_cost<<" edge_dist="<<next_dist<<"\n";
                  if(next_id==goal)
                    return next_dist/K;
                    
                  Map::const_iterator it=dist.find(next_id);
                  if(it==dist.end() || next_dist<it->second){
                    dist[next_id]=next_dist;
                    q.push(std::make_pair(next_dist, next_id));
                  }
                }
    }
    //std::cout<<"not found!\n";
    return 5;
    
}

int main(){
    
    size_t N;
    std::cin>>N;
    Type start=0;
    for(size_t i=0;i<N;i++){
        int ch;
        std::cin>>ch;
        start=start*10+(ch-1);
    }
    
    std::cout<<getDist(start, N)<<std::endl;   
}


