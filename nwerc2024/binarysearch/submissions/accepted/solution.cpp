#include <iostream>
#include <vector>
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
typedef long double ld;

int n,m;
const int MAXN = 300001;
vi A;
int part[2*MAXN] = {0};
vector<vi> D(2*MAXN, vi()); // directed graph

vi topsort;

bool cyclic(){
    vi deg(2*n,0);
    rep(c1,0,2*n){
        trav(y, D[c1]){
            deg[y]++;
        }
    }
    vi Q;
    int seen = 0;
    rep(c1,0,2*n){
        if(deg[c1] == 0)Q.push_back(c1);
    }

    while(sz(Q) > 0){
        int i = Q.back();
        topsort.push_back(i);
        Q.pop_back();
        seen++;
        trav(y, D[i]){
            deg[y]--;
            if(deg[y] == 0)Q.push_back(y);
        }
    }
    return (seen < 2*n);
}

int DP[2*MAXN] = {0};
int longest[4] = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;

    rep(c1,0,n){
        int a;
        cin >> a;
        A.push_back(a);
        part[c1] = a; // same color
        part[n+c1] = 2+a; // different color
    }
    rep(c1,0,m){
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        if(A[a] == A[b]){
            D[a].push_back(b+n);
            D[b].push_back(a+n);
        }
        else{
            D[a+n].push_back(b);
            D[b+n].push_back(a);
        }
    }

    if(cyclic()){
        cout << "infinity\n";
        return 0;
    }

    for(int c1 = 2*n-1; c1 >= 0; c1--){
        int i = topsort[c1];
        trav(y, D[i]){
            DP[i] = max(DP[i], DP[y]);
        }
        DP[i]++;
        longest[part[i]] = max(longest[part[i]], DP[i]);
    }

    int ans = 2*n+1;
    rep(c1,0,4){
        ans = min(ans, longest[c1]);
    }

    cout << ans+1 << "\n";

    return 0;
}
