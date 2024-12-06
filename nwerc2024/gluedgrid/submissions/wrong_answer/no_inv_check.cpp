#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

// 0 indexed template
struct BIT {
    using T = int32_t;
    constexpr static T UNIT = 0;

    static T f(const T& a, const T& b) {
        return a + b;
    }

    int32_t n;
    std::vector<T> f_tree;
    BIT(int32_t n): n(n) {
        f_tree.assign(n + 1, UNIT);
    }

    // data[x] = f(data[x], v)
    void update(int32_t x, T v) {
        for (++x; x <= n; x += (x & -x)) {
            f_tree[x] = f(f_tree[x], v);
        }
    }

    // f applied to range [0..x]
    T query(int32_t x) const {
        T res = UNIT;
        for (++x; x > 0; x -= (x & -x)) {
            res = f(res, f_tree[x]);
        }

        return res;
    }
};

struct Solver {
    static auto fromStdin() -> Solver {
        int32_t h, w;
        std::cin >> h >> w;

        int32_t n = h * w;
        std::vector<bool> fixed(n);

        std::string row;
        row.reserve(w);
        for (auto i = 0; i < h; ++i) {
            std::cin >> row;
            for (auto j = 0; j < w; ++j) {
                fixed[w * i + j] = (row[j] == '#');
            }
        }

        std::vector<int32_t> data(n);
        for (auto i = 0; i < n; ++i) {
            std::cin >> data[i];
            --data[i];
            if (data[i] < 0) {
                assert(i == n - 1);
                data[i] = n - 1;
            }
        }

        return {.h_ = h,
                .w_ = w,
                .isFixed_ = std::move(fixed),
                .base_ = std::move(data),
                .ftree_ = BIT(h * w)};
    }

    auto neighbors(int32_t v) -> std::vector<int32_t> {
        std::vector<int32_t> neighbors;
        neighbors.reserve(4);

        int32_t r = v / w_;
        int32_t c = v % w_;
        for (auto d = 0; d < 4; ++d) {
            int32_t nr = r + dr[d];
            int32_t nc = c + dc[d];
            int32_t idx = nr * w_ + nc;
            if (0 <= nr && nr < h_ && 0 <= nc && nc < w_ && !isFixed_[idx]) {
                neighbors.push_back(idx);
            }
        }

        return neighbors;
    }

    auto checkComponent(std::vector<int32_t> nodes) -> bool {
        std::sort(nodes.begin(), nodes.end());
        std::vector<int32_t> labels;
        labels.reserve(nodes.size());
        for (auto u : nodes) {
            labels.push_back(base_[u]);
        }
        std::sort(labels.begin(), labels.end());

        // BUG: doesn't check inversion
        return nodes == labels;
    }

    auto dfs(int32_t u, int32_t p = -1) -> int32_t {
        timeIn_[u] = curTime_;
        low_[u] = curTime_;
        ++curTime_;
        stk_.push_back(u);

        for (auto v : neighbors(u)) {
            if (v == p) continue;

            if (timeIn_[v] == -1) {
                int32_t start = stk_.size();
                low_[u] = std::min(low_[u], dfs(v, u));
                if (low_[v] >= timeIn_[u]) {
                    // u is an articulation point
                    // process all nodes in the subtree of v and remove them
                    std::vector<int32_t> curComp{stk_.begin() + start, stk_.end()};

                    // component includes u, but don't delete u
                    stk_.resize(start);

                    isValid_ &= checkComponent(std::move(curComp));
                }
            } else {
                low_[u] = std::min(low_[u], timeIn_[v]);
            }
        }

        return low_[u];
    }

    auto canSolve() -> bool {
        int32_t n = h_ * w_;
        curTime_ = 0;
        timeIn_.assign(n, -1);
        low_.assign(n, -1);
        vis_.assign(n, false);
        isValid_ = true;
        dfs(n - 1);
        isValid_ &= checkComponent(std::move(stk_));

        return isValid_;
    }

    static constexpr int32_t dr[]{1, 0, -1, 0};
    static constexpr int32_t dc[]{0, -1, 0, 1};

    int32_t h_, w_;
    std::vector<bool> isFixed_;
    std::vector<int32_t> base_;

    BIT ftree_;

    // DFS variables
    std::vector<int32_t> timeIn_, low_, stk_, vis_;
    int32_t curTime_;

    bool isValid_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solver solver = Solver::fromStdin();

    auto res = solver.canSolve();

    std::cout << (res ? "possible" : "impossible") << '\n';

    return 0;
}
