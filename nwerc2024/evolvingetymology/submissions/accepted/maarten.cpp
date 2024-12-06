#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    long long offset = 1, base = 2;
    while (k > 0) {
        if (k & 1) {
            offset = (offset * base) % n;
        }
        k >>= 1;
        base = (base * base) % n;
    }

    string result;
    for (int i = 0; i < n; ++i) {
        result += s[(i * offset) % n];
    }

    cout << result << endl;
    return 0;
}
