#include <bits/stdc++.h>

using namespace std;

int read_duration()
{
    int m, s;
    char c;
    cin >> m >> c >> s;
    return 60 * m + s;
}

void print_duration(int seconds)
{
    cout << setfill('0') << setw(2) << seconds / 3600 << ":" << setw(2) << (seconds / 60) % 60 << ":" << setw(2) << seconds % 60 << endl;
}

int main()
{
    int n, c;
    cin >> n >> c;
    int sum = -c * (n - 1);
    while (n--) sum += read_duration();
    print_duration(sum);
}
