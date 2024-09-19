#include "validation.h"
#include <set>
using namespace std;

struct fraction {
    int a, b;
    fraction(int c, int d = 1): a(c), b(d) {
        int g = gcd(a, b);
        a /= g, b /= g;
        if (b < 0) a = -a, b = -b;
    }
    fraction operator+(const fraction &f) const {
        return fraction(a*f.b + b*f.a, b*f.b);
    }
    fraction operator-(const fraction &f) const {
        return fraction(a*f.b - b*f.a, b*f.b);
    }
    fraction operator*(const fraction &f) const {
        return fraction(a*f.a, b*f.b);
    }
    fraction operator/(const fraction &f) const {
        return fraction(a*f.b, b*f.a);
    }
    bool operator<(const fraction &f) const {
        return a*f.b < b*f.a;
    }
};

set<fraction> values(vector<int> a) {
    set<fraction> res;
    for (int x: a) res.insert(fraction(x));

    int n = size(a);
    for (int mask = 1; mask+1 < (1 << n); mask++) {
        vector<int> b, c;
        for (int i = 0; i < n; i++) {
            (mask & (1 << i) ? b : c).push_back(a[i]);
        }
        auto left = values(b);
        auto right = values(c);
        for (auto f: left) {
            for (auto g: right) {
                res.insert(f+g);
                res.insert(f-g);
                res.insert(f*g);
                if (g.a != 0) res.insert(f/g);
            }
        }
    }
    return res;
}

int main(int argc, char **argv) {
    ifstream in(argv[1]);
    OutputValidator v(argc, argv);

    int d; in >> d;

    int a = v.read_integer("a", 1, 100);
    v.space();
    int b = v.read_integer("b", 1, 100);
    v.space();
    int c = v.read_integer("c", 1, 100);
    v.newline();

    v.check(a != b && a != c && a != d && b != c && b != d && c != d, "the four numbers must be distinct");

    auto s = values({a, b, c});

    v.check(!s.count(fraction(d)), "d can be expressed using a, b and c");
}
