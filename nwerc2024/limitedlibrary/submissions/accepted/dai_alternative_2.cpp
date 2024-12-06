#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m, x, y, z, cnt = 0, ptr;
int a[100010],
    b[100010],
    dp_low[100010];

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
    ptr = n;
    for (int i = m-1; i >= 0; i--)
    {
        if (cnt == 0) cnt = x, ptr--;
        if (a[ptr] < b[i] || ptr < 0) return !printf("impossible\n");
        cnt--;
    }

    // step 2: dp_low[i] = min last index of unmodified shelves to hold the first i+1 books
    ptr = 0;
    for (int i = 0; i < x; i++)
    {
        while (ptr < n && a[ptr] < b[i]) ptr++;
        dp_low[i] = ptr;
    }
    for (int i = x; i < m; i++)
    {
        while (ptr < n && a[ptr] < b[i]) ptr++;
        dp_low[i] = max(ptr, dp_low[i-x] + 1);
    }

    // step 3: modify the shelves greedily from biggest to smallest
    ptr = m-1, cnt = 0;
    for (int i = n-1; i >= 0; i--)
    {
        //printf("%d %d %d\n", i, ptr, dp_low[ptr-y]);
        if (ptr <= 0) cnt++;
        else if (ptr < y) cnt++, ptr = 0;
        else if (dp_low[ptr-y] < i) cnt++, ptr -= y;
        else ptr -= x;
        //printf("%d\n", cnt);
    }
    printf("%d\n", cnt);
}
