#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m, x, y;
int a[100010], b[100010];

int main()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);

    sort(a, a + n);
    //sort(b, b + m);

    int L = -1, R = n+1;
    while (R - L > 1)
    {
        int M = (L + R) / 2,
            ptr = 0,
            cnt = M > ptr ? y : x;
        for (int i = 0; i < m; i++)
        {
            while (ptr < n && (b[i] > a[ptr] || cnt == 0))
            {
                ptr++;
                cnt = M > ptr ? y : x;
            }
            if (ptr == n) break;
            cnt--;
        }
        if (ptr == n) R = M;
        else L = M;
    }
    if (L == -1) printf("impossible\n");
    else printf("%d\n", L);
}
