// @EXPECTED_RESULTS@: TIME_LIMIT_EXCEEDED, RUN_TIME_ERROR
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

constexpr bool DEBUG = false;

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
        }

        return {.h_ = h,
                .w_ = w,
                .isFixed_ = std::move(fixed),
                .base_ = std::move(data),
                .seen_ = {}};
    }

    auto isDone(const std::vector<int32_t>& data) const -> bool {
        for (auto i = 0; i < h_ * w_ - 1; ++i) {
            if (data[i] != 1 + i) {
                return false;
            }
        }

        return data.back() == 0;
    }

    auto canSolve(std::vector<int32_t> data) -> bool {
        if (auto it = seen_.find(data); it != seen_.end()) {
            return false;
        }

        if constexpr (DEBUG) {
            int32_t invs = 0;
            for (auto i = 0; i < data.size(); ++i) {
                if (data[i] == 0) continue;
                for (auto j = i + 1; j < data.size(); ++j) {
                    if (data[j] == 0) continue;

                    invs += data[i] > data[j];
                }
            }

            if constexpr (DEBUG) {
                std::cerr << "Considering grid:" << std::endl;
                for (auto i = 0; i < h_; ++i) {
                    for (auto j = 0; j < w_; ++j) {
                        std::cerr << data[w_ * i + j] << ' ';
                    }
                    std::cerr << std::endl;
                }
                std::cerr << "Inversions: " << invs << '\n';
                std::cerr << std::endl;;
            }
        }

        if (isDone(data)) {
            return true;
        }

        seen_.insert(data);
        auto idx = std::distance(data.begin(), std::find(data.begin(), data.end(), 0));
        assert(!isFixed_[idx]);

        int32_t r = idx / w_;
        int32_t c = idx % w_;

        for (auto d = 0; d < 4; ++d) {
            int32_t nr = r + dr[d];
            int32_t nc = c + dc[d];
            int32_t ni = w_ * nr + nc;

            if (0 <= nr && nr < h_ && 0 <= nc && nc < w_ && !isFixed_[ni]) {
                std::swap(data[idx], data[ni]);
                if (canSolve(data)) {
                    return true;
                }
                std::swap(data[idx], data[ni]);
            }
        }

        return false;
    }

    static constexpr int32_t dr[]{1, 0, -1, 0};
    static constexpr int32_t dc[]{0, -1, 0, 1};

    int32_t h_, w_;
    std::vector<bool> isFixed_;
    std::vector<int32_t> base_;

    // TODO: Use absl containers for perf
    std::set<std::vector<int32_t>> seen_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Solver solver = Solver::fromStdin();

    auto res = solver.canSolve(solver.base_);

    if constexpr (DEBUG) {
        std::cerr << "Considered " << solver.seen_.size() << " grids\n";
    }

    std::cout << (res ? "possible" : "impossible") << '\n';

    return 0;
}
