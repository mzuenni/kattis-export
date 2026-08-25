//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)

typedef long long ll;
typedef vector<int> vi;
typedef pair<ll, int> pli;
int main()
{
    int n; ll k;
    scanf("%d %lld", &n, &k);

    vi g(n);
    rep(i,0,n)
        scanf("%d", &g[i]);

    sort(g.begin(), g.end());
    int mod = g[0];

    vector<ll> dist(mod, k + 4);
    vector<bool> seen(mod, false);
    for (int x : g) if (x <= k && dist[x % mod] > k)
        dist[x % mod] = x;
    g.erase(g.begin());

    rep(j,0,mod)
    {
        int ma = -1;
        rep(i,0,mod) if (!seen[i])
            if (ma == -1 || dist[ma] > dist[i])
                ma = i;

        if (dist[ma] > k) break;
        seen[ma] = true;
        ll dis = dist[ma];

        for (int x : g)
        {
            int res = (ma + x) % mod;
            if (k >= dis + x && dist[res] > dis + x)
                dist[res] = dis + x;
        }
    }

    cout << (dist[k % mod] <= k ? "possible" : "impossible") << endl;
}
