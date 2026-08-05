/* a bidirectional bfs

   calculates the id (in lexicographical order) of the permutation, 
   rather than using fancy data structures like hash_map
   
   
   this solution saves all known states and not only the border of explored region, there are not that many states, so it does not matter...
   
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <deque>

typedef char Type;
typedef std::vector<Type> Vector;

size_t  permutationIndex(const Vector &vec, size_t radix) {
  size_t result = 0;
  for(size_t i=0;i<vec.size();++i) {
    
    size_t count=0;
    for(size_t j=i+1;j<vec.size();++j)
        count+=vec[j]<vec[i]?1:0;
      
    result += radix * count;
    
     size_t diff=vec.size()-i-1;
     if(diff!=0)
        radix /= diff;
  }

  return result;
}

size_t factorial(size_t N){
 size_t res=1;
 for (size_t i=2;i<=N;i++)
    res*=i;
 return res;
}


void bit_shuffle(Vector &orig, Vector &res, size_t first, size_t second, size_t third){
    res.clear();
    res.reserve(orig.size());
    
    for(size_t i=second;i<third;i++)
        res.push_back(orig[i]);
    for(size_t i=0;i<first;i++)
        res.push_back(orig[i]);
    for(size_t i=third;i<orig.size();i++)
        res.push_back(orig[i]);       
    for(size_t i=first;i<second;i++)
        res.push_back(orig[i]);
}

void bit_shuffle_back(Vector &orig, Vector &res, size_t first, size_t second, size_t third){
    res.clear();
    res.reserve(orig.size());
    
    for(size_t i=first;i<second;i++)
        res.push_back(orig[i]); 
    for(size_t i=third;i<orig.size();i++)
        res.push_back(orig[i]);  
    for(size_t i=0;i<first;i++)
        res.push_back(orig[i]);      
    for(size_t i=second;i<third;i++)
        res.push_back(orig[i]);     
}


int getDist(const Vector &start){
    size_t N=start.size();
    size_t radix=factorial(N-1);
    size_t CNT=radix*N;
    std::vector<Vector> mem(CNT, Vector(N));
    std::vector<int> dist(CNT, -1);
    std::vector<int> start_id(CNT, 0);
    
    std::deque<size_t> q;
    size_t start_index=permutationIndex(start, radix);
    mem[start_index]=start;
    for(size_t i=0;i<N;i++)
      mem[0][i]=i+1;;
    
    
    if(start_index==0)
        return 0;
    

    q.push_back(start_index);
    dist[start_index]=0;
    start_id[start_index]=1;
    
    q.push_back(0);
    dist[0]=0;
    start_id[0]=2;
    
    
    Vector next(N);
    while (!q.empty()){
        size_t index=q.front();
        int d=dist[index];
        q.pop_front();
        for(size_t i=0;i<=N;i++)
            for(size_t j=i;j<=N;j++)
                for(size_t k=j;k<=N;k++){
                  if(start_id[index]==1)
                      bit_shuffle(mem[index], next, i,j,k);
                  else
                      bit_shuffle_back(mem[index], next, i,j,k);
                  size_t next_index=permutationIndex(next, radix);           
                  if(dist[next_index]==-1){
                       mem[next_index]=next;
                       dist[next_index]=d+1;
                       start_id[next_index]=start_id[index];
                       q.push_back(next_index);
                       
                  }
                  else if(start_id[index]!=start_id[next_index]){
                     return dist[index]+dist[next_index]+1;
                  }
                }
    }
    
    return -1;
    
}
int main(){
    
    size_t N;
    std::cin>>N;
    Vector start;
    for(size_t i=0;i<N;i++){
        int ch;
        std::cin>>ch;
        start.push_back(ch-1);
    }
    
    std::cout<<getDist(start)<<std::endl;   
}


