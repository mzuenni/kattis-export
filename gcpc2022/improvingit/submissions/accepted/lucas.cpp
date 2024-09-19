#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long N;
    long long M;

    cin >> N >> M;

    vector<long long> costs(N + 1, 1ll << 62);
    costs[0] = 0;

    for (long long i = 1; i <= N + 1; i++) {
        long long cost;
        cin >> cost;

        for (long long j = 0; j < min(M, N - i + 1); j++) {
            long long value;
            cin >> value;

            costs[i + j] = min(costs[i + j], costs[i - 1] + cost - value);
        }
    }

    cout << costs[N] << "\n";
}