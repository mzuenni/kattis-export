#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int MAXN = 2023;
int n,m;

vi I,INV;
vector<vi> C;

vi P;

bool comp(int i, int j){
    return INV[i] > INV[j];
}

bool geq(vi &ci, vi &cj){
    rep(c1,0,max(sz(ci), sz(cj))){
        if(c1 == sz(ci))return 0;
        if(c1 == sz(cj))return 1;
        if(INV[ci[c1]] < INV[cj[c1]])return 0;
        if(INV[ci[c1]] > INV[cj[c1]])return 1;
    }
    return 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;
    
    I.push_back(0);
    INV.push_back(0);
    C.push_back({});

    rep(c1,0,n){
        P.push_back(0);
    }

    rep(_,0,m){
        char ch;
        int i,j;
        cin >> ch >> i >> j;
        i--;
        j--;
        if(ch == '?'){
            if(INV[P[i]] < INV[P[j]])cout << "<\n";
            if(INV[P[i]] == INV[P[j]])cout << "=\n";
            if(INV[P[i]] > INV[P[j]])cout << ">\n";
        }
        else{
            vi inds = C[P[i]];
            inds.push_back(P[j]);
            sort(all(inds), comp);
            int lo = -1;
            int hi = sz(I);
            while(lo < hi-1){
                int mid = (lo+hi)/2;
                if(geq(C[I[mid]], inds)){
                    hi = mid;
                }
                else{
                    lo = mid;
                }
            }

            if(hi < sz(I) && geq(inds, C[I[hi]])){
                P[i] = I[hi];
            }
            else{
                I.push_back(I.back());
                for(int c1 = sz(I)-2; c1 > hi; c1--){
                    I[c1] = I[c1-1];
                }
                I[hi] = sz(I)-1;
                INV.push_back(0);
                for(int c1 = 0; c1 < sz(INV); c1++){
                    INV[I[c1]] = c1;
                }
                C.push_back(inds);
                P[i] = sz(I)-1;
            }
        }
    }

    return 0;
}
