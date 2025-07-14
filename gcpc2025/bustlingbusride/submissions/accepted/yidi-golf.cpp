#include <bits/extc++.h>
using namespace std;
using ll = long long;
using namespace __gnu_pbds;
template<typename T>
using V=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
int main() {
    ll n,b,D,w,l=0,r=2e18;
    cin>>n>>b>>D>>w;
    vector<ll>a(b),c(n);
    for (ll& e:a)cin>>e;
    for (int i=1;i<b;i++)a[i]+=a[i-1];
    for (ll& e:c)cin>>e,e=a[e-1];
    while (l+1<r){
        ll M=(l+r)/2,P=0;
        for (ll bus=0,t=0,mx=0; P<n; bus++,t=2*w+c[P],mx=0,t=bus*D){
            if(t+2*w+c[P]>M)break;
            V<int>U;
            V<pair<int,int>>S;
            while (P<n){
                mx=max(mx,c[P]),t+=(U.order_of_key(c[P]))*w*2;
                if (U.find(c[P])==U.end())t+=((ll)S.size()-S.order_of_key({c[P],P}))*w*2,U.insert(c[P]);
                S.insert({c[P],P});
                if (t+2*w+mx>M)break;
                P++,t+=2*w;
        }}
        (P<n?l:r)=M;
    }
    cout<<r<<'\n';
}
