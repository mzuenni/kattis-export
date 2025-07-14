#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ll sm = 0, n, m, b, k, A = 1e18;
    cin >> n >> m >> b >> k;
    vector<ll> f(b), h(n), C(b), a(n), a2(b+1), p(3*b+1);
    for (int i=0, j=0, x; i<b; i++) {
        cin >> x;
        a2[i+1] = a2[i] + x;
        while (x--) a[j++] = i;
    }
    vector<vector<pair<int, ll>>> g(n);
    for (int i=0, u, v, w; i<m; i++) {
        cin >> u >> v >> w;
        if (--u > --v) swap(u, v);
        if (a[u] != a[v]) {
            if (u == 0 && v == n-1) sm += f.back() = w;
            else sm += f[a[u]] = w;
        } else g[u].emplace_back(v, w), g[v].emplace_back(u, w);
    }
    for (int i=0, u; i<k; i++) cin >> u, h[u-1] = true, C[a[u-1]]++;
    vector<array<ll, 5>> d(b);
    for (int r=0, o=0, k=2; r<b; o = a2[++r], k=2) {
        int N = a2[r+1] - a2[r];
        vector<int> t={0,N-1};
        for (int i=1; i<N-1; i++) if (h[a2[r] + i]) t.push_back(i), k++;
        vector z(N, vector<ll>(1<<k, 1e18));
        for (int i=0; i<N; i++) z[t[min(i, k-1)]][1<<min(i, k-1)] = 0, z[i][0] = 0;
        for (int M=1; M<(1<<k); M++) {
            priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<>> q;
            for (int i=0; i<N; i++) {
                for (int M2=M; M2>0; M2 = (M2-1) & M) {
                    z[i][M] = min(z[i][M], z[i][M2] + z[i][M^M2]);
                }
                q.push({z[i][M], i});
            }
            while (!q.empty()) {
                auto [val, u] = q.top();
                q.pop();
                if (z[u][M] == val) for (auto [v, w] : g[o + u]) if (z[v - o][M] > z[u][M] + w) z[v - o][M] = z[u][M] + w, q.push({z[v - o][M], v - o});
        }}
        int s = (1<<k) - 1, s2 = s, s3 = s, s4 = s;
        if (!h[o + 0]) s3 ^= 1, s4 ^= 1;
        if (!h[o + N-1]) s2 ^= 2, s4 ^= 2;
        ll x = 0, y = 1e18;
        for (int i=0; i<k; i++) if (s4 >> i & 1) x = z[t[i]][s4];
        for (int i=1; i<(1<<k); i += 4) y = min(y, z[0][i] + z[N-1][s ^ i]);
        if (N>1)d[r] = {z[0][s], z[0][s2], z[N-1][s3], x, y};
    }
    for (int i=0; i<3*b; i++) p[i+1] = p[i] + d[i%b][0];
    for (ll l=0, r=1, c=sm-f[l]; l<b; l=r++, c=sm - f[l]) {
        while (C[r % b] == 0) c -= f[r % b], r++;
        if (r == l + b) A = min(A, d[r % b][3]);
        else A = min(A, c + d[l][1] + d[r%b][2] + p[l+b] - p[r+1]);
        A = min(A, d[l][4] + sm + p[l+b] - p[l+1]);
    }
    cout << A << '\n';
}
