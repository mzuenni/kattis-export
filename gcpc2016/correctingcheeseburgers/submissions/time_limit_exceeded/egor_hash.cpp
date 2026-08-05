/* a normal bfs
   
   uses hash map to track the known states
   
   should tle
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <deque>
#include <unordered_map>

typedef long long int Type;

typedef Type  Info;
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


Type getDist(Type start, size_t N){

    Type goal=goals[N-1];
    if(goal==start) 
        return 0;
        
    Map dist;//first=dist, second=origin 
    std::deque<Type> q;
    
    q.push_back(start);
    dist[start]=0;
     
    
    
    while (!q.empty()){
        Type id=q.front();
        q.pop_front();
        Info info=dist[id];
        info++;//update to use for children
        Vector orig(N);
        decode(id, N, orig);
        //brute force all possibilities
        for(size_t i=0;i<=N;i++)
            for(size_t j=i;j<=N;j++)
                for(size_t k=j;k<=N;k++){
                  Type next_id= bit_shuffle(orig,i,j,k);
                  if(next_id==goal)
                    return info;
                    
                  Map::const_iterator it=dist.find(next_id);
                  if(it==dist.end()){
                       dist.insert(std::make_pair(next_id, info));
                       q.push_back(next_id);                     
                  }
                }
    }
    
    return -1;
    
}

int main(){
    
    size_t N;
    std::cin>>N;
    Type start=0;
    for(size_t i=0;i<N;i++){
        Type ch;
        std::cin>>ch;
        start=start*10+(ch-1);
    }
    
    std::cout<<getDist(start, N)<<std::endl;   
}


