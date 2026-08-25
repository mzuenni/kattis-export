#include <algorithm>
#include <iostream>
#include <utility>
#include <cstdint>
#include <cstring>
#include <queue>
using namespace std;
typedef uint64_t ll;

ll v[20];

ll dist[200001];
priority_queue<pair<ll,ll>> todo;

int main(){
    ll n,k; cin>>n>>k;
    for (int i=0; i<n; i++) cin>>v[i];
    sort(v,v+n);
    ll Q=v[--n];

    memset(dist,-1,sizeof dist);
    todo.push({-v[n],0});
    for (int i=n; i--;)
        todo.push({-v[i],v[i]%Q});

    while (not todo.empty()){
        auto t=todo.top(); todo.pop(); ll x=t.second;
        if (dist[x]==-1) dist[x]=-t.first; else continue;
        for (int i=n; i--;) if (dist[(x+v[i])%Q]==-1) {
            todo.push({-dist[x]-v[i],(x+v[i])%Q});
        }
    }

    if (dist[k%Q]<=k)
        cout<<"possible"<<endl;
    else
        cout<<"impossible"<<endl;
}
