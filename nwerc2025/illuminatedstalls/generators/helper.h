#include <algorithm>
#include <cassert>
#include <array>
#include <set>
#include <map>
#include <vector>

constexpr int MAX_T = 20'000;
constexpr int MIN_N = 4;
constexpr int MAX_N = 150'000;
constexpr int MIN_COORD = 0;
constexpr int MAX_COORD = 1e9;

namespace validator {
    using namespace std;

    bool is_valid(vector<array<Integer, 4>> a, bool check_n = false) {
        Integer n = ssize(a);
        if (check_n) if (n < MIN_N || n > MAX_N) return false;

        map<Integer, vector<pair<Integer, Integer>>> horizontal, vertical;
        for (auto [x1, y1, x2, y2] : a) {
            if (pair{x1, y1} == pair{x2, y2}) return false;
            if (x1 > x2 || y1 > y2) return false;
            if (x1 != x2 && y1 != y2) return false;

            if (x1 == x2) {
                vertical[x1].emplace_back(y1, y2);
            }
            if (y1 == y2) {
                horizontal[y1].emplace_back(x1, x2);
            }
        }

        for (auto mp : array{horizontal, vertical}) {
            for (auto [_, vec] : mp) {
                sort(vec.begin(), vec.end());
                for (int i=1; i<ssize(vec); i++) {
                    if (vec[i].first <= vec[i-1].second) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}

namespace solution {
    using namespace std;
    using ll = Integer;
    #define all(x) std::begin(x), std::end(x)
    constexpr ll INF = 1e18;

    ll len(array<ll, 4>& x) {
        return abs(x[2] - x[0]) + abs(x[3] - x[1]);
    }

    bool solve(vector<array<ll, 4>> a, ll l) {
        int n = ssize(a);

        vector<array<ll, 3>> horis;
        vector<array<ll, 5>> events;
        for (int i=0; i<n; i++) {
            auto [x1, y1, x2, y2] = a[i];
            if (x1 == x2) {
                events.push_back({x1, 1, y1, y2, i});
            } else {
                events.push_back({x1, 0, y1, -1, i});
                events.push_back({x2, 2, y1, -1, i});
                horis.push_back({y1, x1, x2});
            }
        }
        sort(all(events));
        sort(all(horis));

        vector<vector<array<ll, 2>>> inters(n);
        int counter = 0;
        
        set<array<ll, 2>> act;
        for (auto [x, type, y1, y2, ind] : events) {
            if (type == 0) act.insert({y1, ind});
            if (type == 2) act.erase({y1, ind});
            if (type == 1) {
                for (auto it=act.lower_bound({y1, -1}); it!=act.end() && it->at(0) <= y2; it++) {
                    if (counter++ > 10*n) return true;
                    inters[it->at(1)].push_back({y2 - it->at(0), x});
                }
            }
        }

        auto connect = [&](ll y, ll x1, ll x2) {
            if (x2 < x1) swap(x1, x2);
            ll needed = x2 - x1;
            auto it = upper_bound(all(horis), array{y, x1+1, -INF});
            if (it != horis.begin()) {
                it--;
                if (it->at(0) == y) needed -= max((ll)0, it->at(2) - x1);
            }
            it = upper_bound(all(horis), array{y, x2, -INF});
            if (it != horis.begin()) {
                it--;
                if (it->at(0) == y && it->at(2) >= x2) needed -= max((ll)0, x2 - it->at(1));
            }
            return needed;
        };

        for (int i=0; i<n; i++) {
            auto& vec = inters[i];
            sort(all(vec), greater<>());
            set<ll> s = {{-INF, INF}};
            for (auto [h, x] : vec) {
                auto it = s.insert(x).first;
                for (auto x2 : {*prev(it), *next(it)}) {
                    ll d = abs(x2 - x);
                    if (d <= h && connect(a[i][1] + d, x, x2) <= l) return true;
                }
            }
        }

        return false;
    }

    bool has_solution(vector<array<ll, 4>> a, ll l) {
        for (int rot=0; rot<4; rot++) {
            if (solve(a, l)) return true;
            for (auto& [x1, y1, x2, y2] : a) {
                swap(x1, y1), swap(x2, y2);
                y1 = -y1, y2 = -y2;
                swap(y1, y2);
                assert(x1 <= x2 && y1 <= y2);
            }
        }
        return false;
    }

    bool has_solution(vector<array<ll, 4>> a) {
        int n = ssize(a);
        sort(all(a), [&](auto& x, auto& y) {
            return len(x) < len(y);
        });

        for (int i=1; i<=min(n, 6); i++) {
            auto b = a;
            ll l = len(a.end()[-i]);
            b.erase(b.end() - i);
            if (has_solution(b, l)) return true;
        }
        return false;
    }
}
