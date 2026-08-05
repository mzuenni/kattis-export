/*
  
  This program matches every edge to one of the nodes it connects. For given d only d connections to a node are allowed.
  
  Uses binary search to find the minimal value of d.
  
  
  For the matching a slightly changed ... is used.
*/


#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

vector<vi> graph;
vector<vi> reverse_graph;
vi left_;
vector<int> seen;
vi lmate;
vi rmate;

bool bump(int i, int c) {
	if (seen[i] == c) return false;
	seen[i] = c;
	for (auto r: graph[i]) {
		if (r != lmate[i]){
		    if(left_[r]>0){
		      left_[r]--;
		      lmate[i]=r;
		      return true;
		    }
		    else
		       //is there a possibility for switch?
		       for(auto &mate: reverse_graph[r])
		        if(lmate[mate]==r && bump(mate, c)){
		            lmate[i]=r;
		            return true;
		        }
		 }
	}
	return false;
}

void reset(int d){
    std::fill(left_.begin(), left_.end(), d);
    std::fill(seen.begin(), seen.end(), -1); 
    std::fill(lmate.begin(), lmate.end(), -1);
    std::fill(rmate.begin(), rmate.end(), -1);
    for(vi &g:graph)
        g.clear(); 
    for(vi &g:reverse_graph)
        g.clear(); 
}


typedef std::pair<size_t, size_t> Edge;
bool match(const std::vector<Edge> &edges, int d){

    //initialize global data structures
    reset(d);
   
    for(int i=0;i<edges.size();i++){
        //link edge into the graph:
        graph[i].push_back(edges[i].first);
        graph[i].push_back(edges[i].second);
        reverse_graph[edges[i].first].push_back(i);
        reverse_graph[edges[i].second].push_back(i);
        
        //augment:
        if(!bump(i,i))
            return false; 
    }
    
    
    return true;
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
    
    graph.resize(m);
    reverse_graph.resize(n);
    left_.resize(n);
    seen.resize(m);
    lmate.resize(m);
    
    
    std::vector<Edge> edges(m);  
    for(size_t i=0;i<m;i++){
        std::cin>>edges[i].first>>edges[i].second;
        edges[i].first--;edges[i].second--;
   }

    int lower=0;
    int upper=estimate_max_d(edges, n);
    
    while(lower+1<upper){
        int middle=(lower+upper)/2;
        if(match(edges, middle))
            upper=middle;
        else
            lower=middle;
    }
    std::cout<<upper<<"\n";
}


