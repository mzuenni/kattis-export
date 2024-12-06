// This is supposed to be right, but it is wrong.
#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m, x, y, z, cnt = 0, ptr;
int a[100010],
    b[100010],
    dp_low[100010], 
    dp_high[100010];

int main()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);
    sort(a, a + n);
    sort(b, b + m);

    // step 1: check that it is possible to fit all books
    ptr = n, dp_high[m] = n;
    for (int i = m-1; i >= 0; i--)
    {
        if (cnt == 0) cnt = x, ptr--;
        if (a[ptr] < b[i] || ptr < 0) return !printf("impossible\n");
        cnt--;
        dp_high[i] = ptr;
    }

    // step 2: dp_low[i] = min last index of modified shelves to hold the first i books
    ptr = 0;
    for (int i = 0; i < y; i++)
    {
        while (ptr < n && a[ptr] < b[i]) ptr++;
        dp_low[i] = ptr;
    }
    for (int i = y; i < m; i++)
    {
        while (ptr < n && a[ptr] < b[i]) ptr++;
        dp_low[i] = max(ptr, dp_low[i-y] + 1);
    }

    // step 3: binary search the answer
    int L = 0, R = m;
    while (L + 1 < R)
    {
        int M = (L + R) / 2;
        if (dp_low[M] < dp_high[M+1]) L = M;
        else R = M;
    }
    printf("%d\n", n - (m - R + x-1)/x);
}
