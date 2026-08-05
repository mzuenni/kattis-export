/*
  The same as egor_ek_vector.cpp but uses ford-fulkerson rather than edmonds-karp
*/
#include <bits/stdc++.h>
int MAX=2000000000;

struct CapEdge{
    size_t target;
    size_t reverse_edge;
    int cap;
    CapEdge(size_t target, size_t reverse_edge, int cap):
        target(target), reverse_edge(reverse_edge), cap(cap){}
};

typedef std::vector<CapEdge> Neighbors;//first->goal of the edge, second->capacitance
typedef std::vector<Neighbors> Graph;
 
 std::vector<bool> used;
 int augment(Graph &graph, size_t start, size_t end, int min){
    used[start]=true;
    if(start==end)
        return min;
    for(CapEdge &edge:graph[start]){
        if(edge.cap>0 && !used[edge.target]){
            int change=augment(graph, edge.target, end, std::min(min, edge.cap));
            if(change>0){
                edge.cap-=change;
                graph[edge.target][edge.reverse_edge].cap+=change;
                return change;
            }
        }
    }
    return 0;
 }

int ford_fulkerson(Graph &graph, size_t start, size_t end){
    int flow=0;
    used.resize(graph.size());
    while(true){
        std::fill(used.begin(), used.end(), false);
        int add_flow=augment(graph, start, end, MAX); 
        if(add_flow==0)
            break;  
        flow+=add_flow;
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
        int received=ford_fulkerson(graph, n, n+1);
        if(expected==received)
            upper=middle;
        else
            lower=middle;
    }
    std::cout<<upper<<"\n";
}


