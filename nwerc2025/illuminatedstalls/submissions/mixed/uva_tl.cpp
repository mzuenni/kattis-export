///uva: O(n**3) with various optimizations. main difference from correct solution is that instead of fixing a row, and for each column that cuts it look at the two nearest taller
///neighbours, this looks for each column that cuts the same row to the right until it can make an U.
///Tested on a subset of generated tests, this doesn't TL on the tests that lucas_nobound did: `manyintersections.py 10000 1 200000` and `manyintersections.py 200000 1 10000`
///it performs better than paul-quadratic on all tests that it TLed on.
///this TLs/performs near the 8s TL on the following tests: (tested on an i5 8th gen laptop, these might time differently on the contest server)
/// 6-5th-intersections.py 199996 -- 6.44s
/// 4-3rd-intersections.py 200000 -- 7.1s
/// 4-3-twice.py 199996 1 0 -- 3.64s
/// 4-3-twice.py 199996 1 1 -- 3.65s
/// 4-3-twice.py 199996 1 2 -- 3.64s
/// 4-3-twice.py 199996 1 3 -- 3.65s

// On contest hardware this should TLE, but it's AC on the CI.
// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#define aaa system("read -r -p \"Press enter to continue...\" key");
#define dbg(x) std::cerr<<(#x)<<": "<<(x)<<'\n',aaa
#define dbga(x,n) {std::cerr<<(#x)<<"[]: ";for(int _=0;_<n;_++)std::cerr<<x[_]<<' ';std::cerr<<'\n',aaa}
#define dbgs(x) {std::cerr<<(#x)<<"[stl]: ";for(auto _:x)std::cerr<<_<<' ';std::cerr<<'\n',aaa}
#define dbgp(x) std::cerr<<(#x)<<": "<<x.first<<' '<<x.second<<'\n',aaa
#define dbgsp(x) {std::cerr<<(#x)<<"[stl pair]:\n";for(auto _:x)std::cerr<<_.first<<' '<<_.second<<'\n';aaa}
#define sz(x) (int)(x).size()

#define PRINT_YES { std::cout << "yes\n"; goto have_yes; }

const int inf = (1 << 30) - 1;

struct Seg {
    int fix, l, r;

    Seg(int fix, int l, int r): fix(fix), l(l), r(r) {}

    bool operator < (const Seg &oth) const {
        if (fix != oth.fix) return fix < oth.fix;
        return l < oth.l; ///if two segments have the same fix, they can't intersect.
    }
};

int biggest_len_aside_from(std::vector<int> &all_lens, std::array<int, 5> aside) {
    std::sort(aside.begin(), aside.end(), std::greater<int>());
    for (int i = 0; i < sz(aside); i++) {
        if (aside[i] != all_lens[i]) return all_lens[i];
    }
    if (sz(all_lens) >= sz(aside)+1) return all_lens[sz(aside)];
    return -1;
}

///there is at most one row that passes through a column at line `row_fix`, column `passes_through`.
int get_seg_index_intersecting(std::vector<Seg> &rows, int row_fix, int passes_through) {
    int i = std::upper_bound(rows.begin(), rows.end(), Seg(row_fix, passes_through, 0)) - rows.begin() - 1;

    if (i >= 0 && rows[i].fix == row_fix && rows[i].l <= passes_through && passes_through <= rows[i].r) return i;
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);

    int t; std::cin >> t;

    while (t--) {
        int n; std::cin >> n;

        std::vector<Seg> rows, cols;
        std::vector<int> all_lens;
        for (int i = 0; i < n; i++) {
            int x1, y1, x2, y2; std::cin >> x1 >> y1 >> x2 >> y2;
            if (x1 == x2) {
                cols.emplace_back(x1, y1, y2);
                all_lens.push_back(y2-y1);
            } else {
                rows.emplace_back(y1, x1, x2);
                all_lens.push_back(x2-x1);
            }
        }

        std::sort(all_lens.begin(), all_lens.end(), std::greater<int>());
        std::sort(rows.begin(), rows.end());
        std::sort(cols.begin(), cols.end());

        int smallest_fail = inf; ///if I couldn't end a square of length ??, we shouldn't try in the future to end squares >=.
        int cnt_its = 0;
        std::array<int, 5> aside;
        std::array<std::array<int, 2>, 2> aside_cands, aside_saves;
        for (int _ = 0; _ < 2; _++) {
            int i = 0;
            while (i < sz(rows)) {
                int j = i;

                std::vector<int> avail_col_ids; /// any col that cuts any line with fix = rows[i].fix.
                while (j < sz(rows) && rows[j].fix == rows[i].fix) {
                    int z = std::lower_bound(cols.begin(), cols.end(), Seg(rows[j].l, 0, 0)) - cols.begin();
                    while (z < sz(cols) && cols[z].fix <= rows[j].r) {
                        if (cols[z].l <= rows[j].fix && rows[j].fix <= cols[z].r) avail_col_ids.push_back(z);
                        z++;
                    }
                    j++;
                }
                
                if (_ == 0) {
                    cnt_its += sz(avail_col_ids);
                    if (cnt_its > 2*n) PRINT_YES
                }

                for (int x = 0; x < sz(avail_col_ids) - 1; x++) {
                    int z = avail_col_ids[x];
                    while (i < j && rows[i].r < cols[z].fix) i++;

                    if (i < j && rows[i].l <= cols[z].fix) {
                        int y = x+1, t = avail_col_ids[y];
                        ///I currently have fixed rows[i], cols[z] as square sides.
                        int tmp_bstt = std::min(
                            std::max(cols[z].r - rows[i].fix, rows[i].fix - cols[z].l),
                            biggest_len_aside_from(all_lens, std::array<int, 5>{rows[i].r - rows[i].l, cols[z].r - cols[z].l, 0, 0, 0})
                        );

                        while (y < sz(avail_col_ids) && cols[t].fix - cols[z].fix <= std::min(smallest_fail-1, tmp_bstt) &&
                                rows[i].l <= cols[t].fix && cols[t].fix <= rows[i].r) {
                            int dist_plus = std::min(cols[t].r, cols[z].r) - rows[i].fix, dist_minus = rows[i].fix - std::max(cols[t].l, cols[z].l);
                            if (cols[t].fix - cols[z].fix <= std::max(dist_plus, dist_minus)) {
                                aside_cands[0] = {0, 0}; aside_cands[1] = {0, 0};
                                aside_saves[0] = {0, 0}; aside_saves[1] = {0, 0};

                                for (int dist = dist_plus, sign = 1, dir = 0; dir < 2; dir++, dist = dist_minus, sign = -1) {
                                    if (cols[t].fix - cols[z].fix <= dist) {
                                        int ind = get_seg_index_intersecting(rows, rows[i].fix + sign * (cols[t].fix - cols[z].fix), cols[z].fix);
                                        if (ind >= 0) {
                                            aside_cands[dir][0] = rows[ind].r - rows[ind].l;
                                            aside_saves[dir][0] = rows[ind].r - cols[z].fix;
                                        }

                                        ind = get_seg_index_intersecting(rows, rows[i].fix + sign * (cols[t].fix - cols[z].fix), cols[t].fix);
                                        if (ind >= 0) {
                                            aside_cands[dir][1] = rows[ind].r - rows[ind].l;
                                            aside_saves[dir][1] = cols[t].fix - rows[ind].l;
                                        }
                                    }
                                }

                                if (all_lens[3] >= cols[t].fix - cols[z].fix) PRINT_YES
                                else {
                                    aside = {cols[t].r - cols[t].l, cols[z].r - cols[z].l, rows[i].r - rows[i].l, 0, 0};
                                    for (int dir = 0; dir < 2; dir++) {
                                        for (int mask = 1; mask < 4; mask++) {
                                            int save = (mask & 1) * aside_saves[dir][0] + (mask >> 1) * aside_saves[dir][1];
                                            aside[3] = (mask & 1) * aside_cands[dir][0];
                                            aside[4] = (mask >> 1) * aside_cands[dir][1];
                                            if (save >= cols[t].fix - cols[z].fix || biggest_len_aside_from(all_lens, aside) >= cols[t].fix - cols[z].fix - save) PRINT_YES
                                        }
                                    }
                                }

                                smallest_fail = std::min(smallest_fail, cols[t].fix - cols[z].fix);
                                break;
                            }

                            y++;
                            if (y < sz(avail_col_ids)) t = avail_col_ids[y];
                        }
                    }
                }

                i = j;
            }

            std::swap(rows, cols);
        }

        std::cout << "no\n";
        have_yes:;
    }

    return 0;
}
