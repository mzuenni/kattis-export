#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n-k; i++) {
        cout << char('a' + (i % 3));
    }
    for (int i = 0; i < k; i++) {
        cout << 'D';
    }
    cout << endl;
}

