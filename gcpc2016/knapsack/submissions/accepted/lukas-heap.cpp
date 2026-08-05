//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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
    priority_queue<pli, vector<pli>, greater<pli> > q;
    for (int x : g) if (x <= k && dist[x % mod] > k)
    {
        q.push(pli(x, x % mod));
        dist[x % mod] = x;
    }
    g.erase(g.begin());

    for (; !q.empty(); q.pop())
    {
        pli o = q.top();
        if (dist[o.second] < o.first) continue;
        for (int x : g)
        {
            int res = (o.second + x) % mod;
            if (k >= o.first + x && dist[res] > o.first + x)
            {
                dist[res] = o.first + x;
                q.push(pli(dist[res], res));
            }
        }
    }

    cout << (dist[k % mod] <= k ? "possible" : "impossible") << endl;
}
