#include <unordered_map>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <utility>

/*
  The same as egor_ek_better_start.cpp but uses std::vector and mapping to reverse edge rather than std::map
*/

struct CapEdge{
    size_t target;
    size_t reverse_edge;
    int cap;
    CapEdge(size_t target, size_t reverse_edge, int cap):
        target(target), reverse_edge(reverse_edge), cap(cap){}
};

typedef std::vector<CapEdge> Neighbors;//first->goal of the edge, second->capacitance
typedef std::vector<Neighbors> Graph;

typedef std::pair<size_t, int> Pred;//first->index of the reverse_edge, second->bottleneck value, min capacity
typedef std::vector<Pred> Preds;


size_t MAX=2000000000;
//remember the way and the minimal capacitance on the way 

bool bfs(const Graph &graph, size_t start, size_t end, Preds &preds){

    std::fill(preds.begin(), preds.end(), std::make_pair(MAX, MAX));
    std::deque<size_t> q;
    
    preds[start]=std::make_pair(2*MAX, MAX); 
    q.push_back(start);
    while (!q.empty()){
        size_t &cur=q.front();
        for(const auto &edge : graph[cur]){ 
            if(edge.cap>0 && preds[edge.target].first==MAX){
                preds[edge.target]=std::make_pair(edge.reverse_edge, std::min(preds[cur].second, edge.cap));
                q.push_back(edge.target);
                if(edge.target==end)
                    return true;
            }
        }
        q.pop_front();
   }
   return false;
}

int add_flow(Graph &graph, size_t end, const Preds &preds){
    int diff=preds[end].second;
    while(true){
        if(preds[end].second==MAX)
            break;
        CapEdge &back_edge=graph[end][preds[end].first];
        size_t next=back_edge.target;
        CapEdge &edge=graph[next][back_edge.reverse_edge];
        edge.cap-=diff;
        back_edge.cap+=diff;
        end=next;
    }
    return diff;
 }
    
int edmonds_karp(Graph &graph, size_t start, size_t end){
    int flow=0;
    size_t n=graph.size();
    Preds preds(n);
   
    while(bfs(graph, start, end, preds)){     
        flow+=add_flow(graph, end, preds);
    }

    return flow;
}
 
void add_edge(Graph &graph, size_t from, size_t to, int cap){
    CapEdge edge(to, graph[to].size(), cap);
    CapEdge rev_edge(from, graph[from].size(), 0);
    graph[from].push_back(edge);
    graph[to].push_back(rev_edge);
}


typedef std::pair<size_t, size_t> Edge;
int init_graph(Graph &graph, const std::vector<Edge> &edges, int d){  

    size_t n=graph.size();
    for(auto &aList:graph)
        aList.clear();
    
    std::vector<int> cnts(n,0);
    
    //try to minimize the number of outgoing edges in greedy manier:
    for(const auto &edge:edges){
         if(cnts[edge.first]<cnts[edge.second]){ 
             cnts[edge.first]++;
             add_edge(graph, edge.first, edge.second, 1);
         }
         else{
             cnts[edge.second]++;
             add_edge(graph, edge.second, edge.first, 1);
         }
    }
    
    int expected=0;
    for(size_t i=0;i<n-2;i++){
        if(cnts[i]>d){
            int needed=cnts[i]-d;
            add_edge(graph, n-2, i, needed);
            expected+=needed;
        }
        if(cnts[i]<d)
            add_edge(graph, i, n-1, d-cnts[i]);
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


