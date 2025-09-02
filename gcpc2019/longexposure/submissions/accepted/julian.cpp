// O(n^2 log n + n * h * w), using coordinate compression

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> interval;

struct rectangle {
    ll x1, x2, y1, y2;
};

vector<ll> x_coords, y_coords;
unordered_map<ll, int> compress_x, compress_y;
vector<rectangle> rectangles;

constexpr char WHITE = 0, BLACK = 1, GREY = 2;

ll dist_sq(ll x, ll y)
{
    return x * x + y * y;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x2 += x1; y2 += y1;
        rectangles.push_back({x1, x2, y1, y2});
        x_coords.push_back(x1);
        x_coords.push_back(x2);
        y_coords.push_back(y1);
        y_coords.push_back(y2);
    }

    for (auto p: {make_pair(&x_coords, &compress_x), make_pair(&y_coords, &compress_y)}) {
        auto& coords = *(p.first);
        auto& compress = *(p.second);
        coords.push_back(numeric_limits<int>::min() / 2);
        coords.push_back(numeric_limits<int>::max() / 2);
        coords.push_back(0);
        sort(coords.begin(), coords.end());
        coords.resize(distance(coords.begin(), unique(coords.begin(), coords.end())));
        for (size_t i = 0; i < coords.size(); ++i) compress[coords[i]] = i;
    }

    vector<vector<char>> color(x_coords.size() - 1, vector<char>(y_coords.size() - 1, WHITE));
    for (rectangle r: rectangles) {
        for (int x = compress_x[r.x1]; x < compress_x[r.x2]; ++x) {
            for (int y = compress_y[r.y1]; y < compress_y[r.y2]; ++y) {
                color[x][y] = BLACK;
            }
        }
    }

    vector<interval> black, white;
    white.reserve(color.size() * color.front().size());
    for (size_t i = 0; i < color.size(); ++i) {
        for (size_t j = 0; j < color.front().size(); ++j) {
            ll x1 = x_coords[i], x2 = x_coords[i + 1], y1 = y_coords[j], y2 = y_coords[j + 1];
            auto d1 = dist_sq(x1, y1), d2 = dist_sq(x1, y2), d3 = dist_sq(x2, y1), d4 = dist_sq(x2, y2);
            ll maxi = max(max(d1, d2), max(d3, d4));
            ll mini = min(min(d1, d2), min(d3, d4));

            if (color[i][j] == BLACK) black.emplace_back(mini, maxi);
            else white.emplace_back(mini, maxi);
        }
    }

    for (auto v: {&black, &white}) {
        auto& intervals = *v;
        sort(intervals.begin(), intervals.end());
        vector<interval> result;
        for (auto i: intervals) {
            if (result.size() && i.first <= result.back().second) {
                result.back().second = max(result.back().second, i.second);
            } else result.push_back(i);
        }
        intervals = result;
    }

    vector<pair<interval, char>> v;
    v.reserve(black.size() + white.size());
    for (auto i: black) v.emplace_back(i, BLACK);
    for (auto i: white) v.emplace_back(i, WHITE);
    sort(v.begin(), v.end());

    vector<pair<interval, char>> result;
    result.push_back({{0, 0}, BLACK});
    for (auto p: v) {
        auto i = p.first;
        if (i.first <= result.back().first.second) {
            auto t = result.back().first.second;
            result.back().first.second = i.first;
            if (i.second > t) {
                result.push_back({{i.first, t}, GREY});
                result.push_back({{t, i.second}, p.second});
            } else {
                result.push_back({{i.first, i.second}, GREY});
                result.push_back({{i.second, t}, (BLACK + WHITE - p.second)});
            }
        } else {
            result.push_back(p);
        }
    }

    ll sum[3] = {0, 0, 0};
    for (auto p: result) {
        sum[p.second] += p.first.second - p.first.first;
    }

    cout << std::fixed << std::setprecision(7) << M_PI * sum[BLACK] << "\n" << M_PI * sum[GREY] << "\n";
}
