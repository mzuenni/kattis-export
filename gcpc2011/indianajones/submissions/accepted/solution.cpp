#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cassert>

using namespace std;

const int MaxN = (int)1e5 + 5;

int in[MaxN];

vector <int> G[MaxN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    scanf("%d", &t);

    while (t--) {
        int n, h, b, a;
        scanf("%d%d", &n, &h);

        assert(1 <= n && n <= 1e5);
        assert(0 <= h && h <= 1e5);

        for (int i = 0; i < n; ++i) {
            G[i].clear();
            in[i] = 0;
        }
        for (int i = 0; i < h; ++i) {
            scanf("%d%d", &a, &b);
            assert(1 <= a && a <= n);
            assert(1 <= b && b <= n);
            assert(a != b);
            --a, --b;
            G[a].push_back(b);
            ++in[b];
        }

        queue  <int> q;
        vector <int> v;
        for (int i = 0; i < n; ++i) {
            if (!in[i]) {
                q.push(i);
                v.push_back(i);
            }
        }

        bool mult = q.size() > 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int add = 0;
            for (int i = 0; i < G[u].size(); ++i) {
                if (--in[G[u][i]] == 0) {
                    q.push(G[u][i]);
                    v.push_back(G[u][i]);
                    ++add;
                }
            }

            mult |= add > 1;
        }

        bool sol = 1;
        for (int i = 0; i < n; ++i) {
            sol &= in[i] == 0;
        }

        if (!sol) {
            printf("recheck hints");
        } else if (mult) {
            printf("missing hints");
        } else {
            for (int i = 0; i < v.size(); ++i) {
                if (i != 0) {
                    printf(" ");
                }
                printf("%d", v[i] + 1);
            }
        }
        printf("\n");
    }

    return 0;
}
