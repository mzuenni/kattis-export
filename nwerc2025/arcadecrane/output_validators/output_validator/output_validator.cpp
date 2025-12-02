#include <iostream>
#include "validation.h"
using namespace std;

const int k = 3;

int main(int argc, char **argv) {
    std::ifstream in(argv[1]);
    std::ifstream ans(argv[2]);
    OutputValidator v(argc, argv);

    int n; in >> n;
    vector<int> a(n);
    for (int &x: a) in >> x;

    int q = v.read_integer("q", 0, 5000);
    v.newline();

    for (int r = 0; r < q; r++) {
        int i = v.read_integer("i", 1, n-k+1);
        v.space();
        int j = v.read_integer("j", 1, n-k+1);
        v.newline();

        i--, j--;

        if (i < j) {
            rotate(a.begin()+i, a.begin()+i+k, a.begin()+j+k);
        } else if (i > j) {
            rotate(a.begin()+j, a.begin()+i, a.begin()+i+k);
        }
    }
    v.check(is_sorted(a.begin(), a.end()), "not sorted");
}
