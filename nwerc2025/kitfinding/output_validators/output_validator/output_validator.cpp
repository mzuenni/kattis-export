#include <string>
#include <vector>
#include "validation.h"
using namespace std;

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    int h, w, k, i, t;
    in >> h >> w >> k >> i >> t;

    vector<string> a(h);
    for (string &s: a) {
        s = v.read_string("a", w, w, "KITkit");
        for (char &c: s) c = toupper(c);
        v.newline();
    }

    auto is = [&](int i, int j, char c) {
        return 0 <= i && i < h && 0 <= j && j < w && a[i][j] == c;
    };

    int ck = 0, ci = 0, ct = 0, ckit = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ck += a[i][j] == 'K';
            ci += a[i][j] == 'I';
            ct += a[i][j] == 'T';
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    bool ok = true;
                    for (int k = 0; k < 3; k++) {
                        ok = ok && is(i+k*di, j+k*dj, "KIT"[k]);
                    }
                    ckit += ok;
                }
            }
        }
    }
    v.check(ck == k, "incorrect number of K: should be ", k, ", but found ", ck);
    v.check(ci == i, "incorrect number of I: should be ", i, ", but found ", ci);
    v.check(ct == t, "incorrect number of T: should be ", t, ", but found ", ct);
    v.check(ckit == 1, "should have exactly 1 KIT, but found ", ckit);
}
