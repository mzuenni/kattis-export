#include <unordered_map>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <utility>

/*
  This program solves the dual problem:
        find minimal d, such that there are no more than d **outgoing** edges in every node.
        
  For a given value d:
    1. start with an arbitrary assigment of directions. Assign capacity 1 to every directed edge.
    
    2. consider the nodes: 
         if there are more than d outgoing edges: add an edge from source with capacity #outgoing-d (that means, we need to change the orientation of #outgoing-d edges)
         if there are less than d outgoning edges: add an edge to sink with capacity d-#outgoing (that means we are allowed to change the orientation for up to d-#outgoing edges)
         
    3. run max-flow algorithm (edmonds karp it this case), if all edges from the source are saturated it is possible to find a solution for d
    
    
 
  use binary search to find the minimal value of d
*/

typedef std::unordered_map<size_t, int> Neighbors;//first->goal of the edge, second->capacitance
typedef std::vector<Neighbors> Graph;

typedef std::pair<size_t, int> Pred;//first->index, second->bottleneck value, min capacity
typedef std::vector<Pred> Preds;

size_t MAX=2000000000;
//remember the way and the minimal capacitance on the way 

bool bfs(const Graph &graph, size_t start, size_t end, Preds &preds){

    std::fill(preds.begin(), preds.end(), std::make_pair(MAX, MAX));
    std::deque<size_t> q;
    
    preds[start]=std::make_pair(start, MAX); 
    q.push_back(start);
    while (!q.empty()){
        size_t &cur=q.front();
        for(const auto &next : graph[cur]){ 
            if(preds[next.first].first==MAX){
                preds[next.first].first=cur;
                preds[next.first].second=std::min(preds[cur].second, next.second);
                q.push_back(next.first);
                if(next.first==end)
                    return true;
            }
        }
        q.pop_front();
   }
   return false;
}

void update_edge(Neighbors &aList, size_t target, int diff){
    Neighbors::iterator it=aList.find(target);
    if(it==aList.end())
        aList.insert(std::make_pair(target, diff));
    else
        it->second+=diff;
} 

int add_flow(Graph &graph, size_t end, const Preds &preds){
    int diff=preds[end].second;
    while(preds[end].first!=end){
        size_t next=preds[end].first;
         //reduce:  
        Neighbors::iterator it=graph[next].find(end);
        if(it->second==diff)
            graph[next].erase(it);
        else
           it->second-=diff;
           
        //backflow:
        update_edge(graph[end], next, diff);
        end=next;
    }
    return diff;
 }
 
void printGraph(Graph &graph){
    for(size_t i=0;i<graph.size();i++){
      for(auto &entry : graph[i])
          std::cout<<i<<"->"<<entry.first<<"("<<entry.second<<"), ";
      std::cout<<"\n";
    }
 }
    
int edmonds_karp(Graph &graph, size_t start, size_t end){
    int flow=0;
    size_t n=graph.size();
    Preds preds(n);
    
    while(bfs(graph, start, end, preds))       
        flow+=add_flow(graph, end, preds);

    return flow;
}
 
typedef std::pair<size_t, size_t> Edge;
int init_graph(Graph &graph, const std::vector<Edge> &edges, int d){  

    size_t n=graph.size();
    for(auto &aList:graph)
        aList.clear();
    
    std::vector<int> cnts(n,0);
    
    for(const auto &edge:edges){
         cnts[edge.first]++;
         update_edge(graph[edge.first], edge.second, 1);
    }
    
    int expected=0;
    for(size_t i=0;i<n-2;i++){
        if(cnts[i]>d){
            int needed=cnts[i]-d;
            update_edge(graph[n-2], i, needed);
            expected+=needed;
        }
        if(cnts[i]<d)
            update_edge(graph[i], n-1, d-cnts[i]);
    }
    
    return expected;
}

int estimate_max_d(const std::vector<Edge> &edges, int n){ 
    std::vector<int> cnts(n,0);
    for(const auto &edge:edges)
         if(cnts[edge.first]<cnts[edge.second])
             cnts[edge.first]++;
         else
             cnts[edge.second]++;
    
    return *std::max_element(cnts.begin(), cnts.end());
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

    Graph graph(n+2);
    int lower=0;
    int upper=estimate_max_d(edges, n);
    
    while(lower+1<upper){
        int middle=(lower+upper)/2;
        int expected=init_graph(graph, edges, middle);
        int received=edmonds_karp(graph, n, n+1);
        if(expected==received)
            upper=middle;
        else
            lower=middle;
    }
    std::cout<<upper<<"\n";
}


