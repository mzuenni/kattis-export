#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
int a[100010], b[100010], dp[2][100010];

int main()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    sort(a+1, a + n+1);
    sort(b+1, b + m+1);
    // dp[i][j] = maximum possible number of modified racks, if one considers the first i racks and the first j books
    // dp[i][j] depends only one dp[i-1][...], so there is no memory issue.
    int ptr = 0;
    bool cur = 1, pre = 0;
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        dp[cur][0] = i;
        for (int j = 1; j <= m; j++)
        {
            if (a[i] < b[j])
            {
                dp[cur][j] = -1;
                break;
            }
            else
            {
                dp[cur][j] = dp[pre][max(j - x, 0)];
                if (dp[pre][max(j - y, 0)] >= 0) dp[cur][j] = max(dp[cur][j], dp[pre][max(j - y, 0)] + 1);
            }
        }
        swap(cur, pre);
    }
    if (dp[pre][m] == -1) printf("impossible\n");
    else printf("%d\n", dp[pre][m]);
}