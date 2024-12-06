#include "validation.h"

int main(int argc, char** argv) {
    InputValidator v(argc, argv);
    int h = v.read_integer("h", 1, 500);
    v.space();
    int w = v.read_integer("w", 1, 500);
    v.newline();

    std::vector<std::string> blocked(h);
    for (int i = 0; i < h; i++) {
        blocked[i] = v.read_string("blocked", w, w, ".#");
        v.newline();
    }

    std::vector<std::vector<int>> a(h, std::vector<int>(w));
    for (int i = 0; i < h; i++) {
        auto row = v.read_integers("a", w, 0, h*w-1);
        for (int j = 0; j < w; j++) {
            a[i][j] = row[j];
        }
    }

    std::vector<int> mark(h*w);
    for (const auto &b: a) for (int x: b) {
        v.check(!mark[x], "a: Value ", x, " seen twice, but must be unique!");
        mark[x] = 1;
    }

    v.check(a[h-1][w-1] == 0, "bottom right must be 0!");

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            v.check(blocked[i][j] == '.' || a[i][j] == i*w+j+1, "unmovable tiles must be in the correct spot!");
        }
    }

    // Check simple connectedness using a Union Find data structure:
    // - Connect neighboring cells if they are both movable or both unmovable.
    // - Connect all unmovable cells on the edge to a node representing the outside of the grid.
    // - The movable tiles are simply connected iff there are at most 2 connected components.

    std::vector<int> parent(h*w+1), height(h*w+1);
    std::iota(std::begin(parent), std::end(parent), 0);

    auto find = [&](int i) {
        while (parent[i] != i) i = parent[i];
        return i;
    };

    auto join = [&](int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        if (height[i] < height[j]) std::swap(i, j);
        parent[j] = i;
        if (height[i] == height[j]) height[i]++;
    };

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (blocked[i][j] == '#' && (i == 0 || j == 0 || i == h-1 || j == w-1)) {
                join(i*w+j, h*w);
            }
            if (i+1 < h && blocked[i][j] == blocked[i+1][j]) {
                join(i*w+j, (i+1)*w+j);
            }
            if (j+1 < w && blocked[i][j] == blocked[i][j+1]) {
                join(i*w+j, i*w+(j+1));
            }
        }
    }

    int C = 0;
    for (int k = 0; k <= h*w; k++) {
        C += find(k) == k;
    }
    v.check(C <= 2, "movable tiles must form a simply connected region!");
}
