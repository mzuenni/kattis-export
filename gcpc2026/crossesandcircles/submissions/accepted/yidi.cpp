#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
#define all(x) ::begin(x), ::end(x)
#define debug(x...) [](auto&& ...y){ cerr << "["#x"]:"; ((cerr << ' ' << y), ...) << endl; }(x)

int main() {
    bool swapped = false;
    auto place = [&](int x, int y) {
        if (swapped) swap(x, y);
        cout << x << ' ' << y << '\n';
        cin >> x >> y;
        if (swapped) swap(x, y);
        return pair{x, y};
    };

    if (place(5, 5).first == 5) swapped = true;
    place(5, place(5, 4).second == 3 ? 6 : 3);
}
