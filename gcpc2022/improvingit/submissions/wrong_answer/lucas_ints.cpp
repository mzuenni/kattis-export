#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long N;
    long long M;

    cin >> N >> M;

    vector<int> costs(N + 1, 1ll << 30);
    costs[0] = 0;

    for (long long i = 1; i <= N + 1; i++) {
        int cost;
        cin >> cost;

        for (long long j = 0; j < min(M, N - i + 1); j++) {
            int value;
            cin >> value;

            costs[i + j] = min(costs[i + j], costs[i - 1] + cost - value);
        }
    }

    cout << costs[N] << "\n";
}