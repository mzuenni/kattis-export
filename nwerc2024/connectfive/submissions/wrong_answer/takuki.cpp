#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

int main() {
    vector<pair<long long, long long>> p(5);
    for (int i = 0; i < 5; i++) {
        cin >> p[i].x >> p[i].y;
    }

    long long ans = 0;

    sort(p.begin(), p.end(), [&](auto a, auto b) {
        return a.x < b.x;
    });
    ans += abs(p[0].x - p[1].x);
    p[0].x = p[1].x;
    ans += abs(p[4].x - p[3].x);
    p[4].x = p[3].x;

    sort(p.begin(), p.end(), [&](auto a, auto b) {
        return a.y < b.y;
    });
    ans += abs(p[0].y - p[1].y);
    p[0].y = p[1].y;
    ans += abs(p[4].y - p[3].y);
    p[4].y = p[3].y;

    sort(p.begin(), p.end(), [&](auto a, auto b) {
        if (a.y == b.y) {
            return a.x < b.x;
        }
        return a.y < b.y;
    });

    auto dist = [&](int i, int j) {
        return abs(p[i].x - p[j].x) + abs(p[i].y - p[j].y);
    };

    if (p[0] == p[1] && p[3] == p[4]) {
        /**
         *  ....4      4....
         *  .....      .....
         *  ..2..  or  ..2..
         *  .....      .....
         *  0....      ....0
        **/

        ans += dist(0, 4);
    } else if (p[0] == p[1]) {
        /**
         *  ..3.4      3.4..
         *  .....      .....
         *  ....2  or  2....
         *  .....      .....
         *  0....      ....0
        **/

        ans += dist(0, 2);
        ans += dist(2, 3);
        ans += dist(2, 4);
    } else if (p[3] == p[4]) {
        /**
         *  4....      ....4
         *  .....      .....
         *  ....2  or  2....
         *  .....      .....
         *  ..0.1      0.1..
        **/

        ans += dist(4, 2);
        ans += dist(2, 0);
        ans += dist(2, 1);
    } else {
        /**
         *  3...4      3...4      3...4      ..3.4      3.4..
         *  .....      .....      .....      .....      .....
         *  ..2..  or  2....  or  ....2  or  2....  or  ....2
         *  .....      .....      .....      .....      .....
         *  0...1      ..0.1      0.1..      0...1      0...1
        **/

        ans += 2 * max(dist(0, 4), dist(1, 3));

        if (p[0].x < p[2].x && p[2].x < p[1].x) {
            /**
             *  3...4
             *  .....
             *  ..2..
             *  .....
             *  0...1
            **/

            ans += min(dist(0, 1), dist(0, 3));
        }
    }
    cout << ans << '\n';
    return 0;
}
