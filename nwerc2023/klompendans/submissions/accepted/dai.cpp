#include <bits/stdc++.h>
using namespace std;

int a, b, c, d, ans = 0, n;
bool ballroom[1010][1010][2];

void dfs(int x, int y, bool type)
{
    if (x < 0 || x >= n || y < 0 || y >= n) return;
    if (ballroom[x][y][type]) return;
    ballroom[x][y][type] = true;
    int dx = type ? a : c, dy = type ? b : d;
    dfs(x+dx, y+dy, !type);
    dfs(x-dx, y-dy, !type);
    dfs(x+dx, y-dy, !type);
    dfs(x-dx, y+dy, !type);
    dfs(x+dy, y+dx, !type);
    dfs(x-dy, y-dx, !type);
    dfs(x+dy, y-dx, !type);
    dfs(x-dy, y+dx, !type);
}

int main()
{
    scanf("%d%d%d%d%d", &n, &a, &b, &c, &d);
    dfs(0, 0, 1);
    dfs(0, 0, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) ans += ballroom[i][j][0] | ballroom[i][j][1];
    }
    printf("%d\n", ans);
    cerr << ans << '\n';
}