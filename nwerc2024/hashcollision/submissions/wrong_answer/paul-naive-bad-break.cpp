#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;

    for (int c = 1; c <= n; c++) {
        for (int r = 1; r <= n; r++) {
            cout << '?' << ' ' << c << ' ' << r << endl;
            int h; cin >> h;
            if (h == c) {
                cout << '!' << ' ' << c << ' ' << r << endl;
                break;
            }
        }
    }
}
