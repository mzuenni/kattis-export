// using as states (current_server, predecessor_server)
//       as edges (current_server, predecessor_server)->(next_server, current_server) with weight time of current_server
//      
// and bellman ford on the graph starting in (0, XXX) and ending in (n-1, XXX), adjusting the costs with the time of the of the last server

//running time O(n^4)

#include <bits/stdc++.h>
using namespace std;
#define MAX 1000000000

struct Edge{
  size_t current;
  size_t predecessor;
  size_t next;
  size_t cost;
  Edge(size_t c, size_t p, size_t n, size_t co): current(c), predecessor(p), next(n), cost(co){}
};

int main(){
    size_t n;
    cin >> n;
    size_t time;
    vector<Edge> edges;

    for(size_t i=0;i<n;i++){
        size_t m;
        cin >> m >> time;
        for (size_t j=0;j<m;j++){
            size_t s, x;
            cin >> s >> x;
            x--;//offset!
            set<size_t> forbidden;
            for(size_t k=0;k<s;k++){
                size_t cur;cin>>cur;
                forbidden.insert(cur);
            }
            for(size_t parent=0;parent<n;parent++)
                if(parent!=i && forbidden.find(parent+1)==forbidden.end())
                    edges.push_back(Edge(i, parent, x, time));
        }
    }

    
    typedef vector<size_t> vs;
    vector<vs> dists(n,vs(n,MAX)); 

    for(size_t i=0;i<n;i++)
       dists[0][i]=time;//don't forget the time from the last server
       
    //do bellman ford:
    bool changed=true;
    while(changed){
        changed=false;
        for(const auto &edge: edges){
            size_t next_dist=dists[edge.current][edge.predecessor]+edge.cost;//don't mind if not set-> than no improvement anyway
            size_t &cur_best=dists[edge.next][edge.current];
            if(next_dist<cur_best){
                cur_best=next_dist;
                changed=true;
            }      
        }   
    }


    size_t best=MAX;
    for(size_t i=0;i<n;i++)
      best=min(best, dists[n-1][i]);
      
    if(best==MAX)
        cout << "impossible" << endl;
    else
        cout << best << endl;
}


