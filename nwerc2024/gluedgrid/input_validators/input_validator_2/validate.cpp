#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

struct DSU {
    int32_t n;
    // uf[x] = parent of x or negative size of component
    std::vector<int32_t> uf;
    DSU(int32_t n): n(n) {
        uf.assign(n, -1);
    }

    int32_t find(int32_t x) {
        return uf[x] < 0 ? x : (uf[x] = find(uf[x]));
    }

    bool merge(int32_t x, int32_t y) {
        int32_t xr = find(x);
        int32_t yr = find(y);
        if (xr == yr)
            return 0;

        if (uf[yr] < uf[xr]) {
            uf[yr] += uf[xr];
            uf[xr] = yr;
        } else {
            uf[xr] += uf[yr];
            uf[yr] = xr;
        }

        return 1;
    }

    bool is_same(int32_t x, int32_t y) {
        return find(x) == find(y);
    }
};

constexpr int KATTIS_SUCCESS = 42;
constexpr int KATTIS_FAILURE = 43;

int main() {
    // Syntax and ranges are checked by CTD. This verifies a single connected component, no holes, fixed cells are correct, etc.
    int32_t h, w;
    std::cin >> h >> w;

    std::vector<bool> isFixed;
    isFixed.reserve(h * w);
    for (auto i = 0; i < h; ++i) {
        std::string row;
        std::cin >> row;
        for (char c : row) {
            isFixed.push_back(c == '#');
        }
    }

    if (isFixed.back()) {
        std::cerr << "Last tile is fixed, and it cannot be!" << std::endl;

        return KATTIS_FAILURE;
    }

    std::vector<bool> seen(h * w, false);
    std::vector<int32_t> labels;
    labels.reserve(h * w);
    for (auto i = 0; i < h; ++i) {
        for (auto j = 0; j < w; ++j) {
            int32_t x;
            std::cin >> x;
            if (seen[x]) {
                std::cerr << "Duplicate label " << x << std::endl;
                return KATTIS_FAILURE;
            }

            seen[x] = true;
            labels.push_back(x);
        }
    }

    if (labels.back() != 0) {
        std::cerr << "0 was not the last tile in the grid!" << std::endl;
        return KATTIS_FAILURE;
    }

    for (auto i = 0; i < h * w; ++i) {
        if (isFixed[i] && labels[i] != (i + 1)) {
            std::cerr << "Expected fixed tile " << (i + 1) << " to be correct, but found value " << labels[i] << std::endl;
            return KATTIS_FAILURE;
        }
    }

    DSU dsu(h * w + 1);
    for (auto i = 0; i < h * w; ++i) {
        auto r = i / w;
        auto c = i % w;
        if (c != w - 1 && isFixed[i] == isFixed[i + 1]) {
            dsu.merge(i, i + 1);
        }
        if (r != h - 1 && isFixed[i] == isFixed[i + w]) {
            dsu.merge(i, i + w);
        }
        if (isFixed[i] && (r == 0 || c == 0 || r == h - 1 || c == w - 1)) {
            dsu.merge(h * w, i);
        }
    }

    int32_t comps = 0;
    for (auto i = 0; i <= h * w; ++i) if (i == dsu.find(i)) {
        ++comps;
    }

    if (comps != 2) {
        std::cerr << "Expected exactly one '.' comp and all '#' comps on border, but got " << comps << "connected components" << std::endl;

        return KATTIS_FAILURE;
    }

    return KATTIS_SUCCESS;
}
