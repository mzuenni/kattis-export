#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const double INF = numeric_limits<double>::infinity();

ll h, w, r, s;
vector<int> stamina;

vector<vector<double>> dijkstra(vector<vector<pair<int, double>>>& adj, int start) {
    int n = adj.size();
    vector<vector<double>> dist(n, vector<double>(s + 1, INF));
    queue<tuple<double, int, int>> q; // distance, node id, stamina
    q.emplace(0, start, s);
    while (q.size()) {
        double d;
        int v, current_s;
        tie(d, v, current_s) = q.front();
        q.pop();
        if (dist[v][current_s] <= -d) continue;
        dist[v][current_s] = -d;
        for (auto p: adj[v]) {
            int new_s = current_s - stamina[p.first];
            if (new_s >= 0) {
                auto dd = d - p.second;
                if (dist[p.first][new_s] > -dd) {
                    q.emplace(dd, p.first, new_s);
                }
            }
        }
    }
    return dist;
}

ll sqr(ll l)
{
    return l * l;
}

double dist(pair<ll, ll> a, pair<ll, ll> b)
{
    return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

int main()
{
    cin >> h >> w >> r >> s;
    vector<string> v(h);
    for (string& str: v) cin >> str;

    vector<pair<ll, ll>> pos; // hold id -> position
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (v[y][x] != '.') {
                stamina.push_back(v[y][x] - '0');
                pos.push_back({y, x});
            }
        }
    }

    int top_hold = 0, bottom_hold = pos.size() - 1;
    s -= stamina[bottom_hold];

    if (s < 0) {
        cout << "impossible\n";
        return 0;
    } else if (s > w * h * 9) s = w * h * 9;

    vector<vector<pair<int, double>>> adj(pos.size());
    for (size_t i = 0; i < pos.size(); ++i) {
        for (size_t j = i + 1; j < pos.size(); ++j) {
            double d = dist(pos[i], pos[j]);
            if (d <= r) {
                adj[i].push_back({j, d});
                adj[j].push_back({i, d});
            }
        }
    }

    auto dist = dijkstra(adj, bottom_hold);

    double result = *(min_element(dist[top_hold].begin(), dist[top_hold].end()));
    if (result >= INF) cout << "impossible\n";
    else cout << setprecision(6) << fixed << result << "\n";
}
