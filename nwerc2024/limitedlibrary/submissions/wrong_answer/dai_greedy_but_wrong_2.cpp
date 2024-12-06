#include <stdio.h>
#include <algorithm>
using namespace std;

int n, m, x, y, z, cnt = 0, ptr;
int a[100010],
    b[100010],
    pos_in_unmodified_packing[100010],
    lower_lim_in_modified_packing[100010],
    histogram[100010];

int main()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    z = x - y;
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < m; i++)
        scanf("%d", &b[i]);

    sort(a, a + n);
    sort(b, b + m);

    // step 1: find the greedy packing with no shelf modified
    ptr = n;
    for (int i = m-1; i >= 0; i--)
    {
        if (cnt == 0) cnt = x, ptr--;
        if (a[ptr] < b[i] || ptr < 0) return !printf("impossible\n");
        cnt--;
        pos_in_unmodified_packing[i] = cnt + ptr * x;
    }


    // step 2: for each book, find how much we can push it toward smaller shelves
    int ptr = 0, cnt = 0;
    for (int i = 0; i < m; i++)
    {
        if (a[ptr] < b[i]) cnt = 0;
        while (a[ptr] < b[i] && ptr < n) ptr++;
        lower_lim_in_modified_packing[i] = ptr * x + cnt;
        cnt++;
    }

    // step 3: build the histogram
    for (int i = 0; i < m; i++) histogram[i] = pos_in_unmodified_packing[i] - lower_lim_in_modified_packing[i];
    for (int i = 0; i < m-1; i++) histogram[i+1] = min(histogram[i+1], histogram[i]);
    // step 4: find the maximum number of shelves
    int ans = 0, sum = 0;
    for (int i = m-1; i >= 0; i--)
    {
        if (sum + z <= histogram[i]) sum += z, ans++;
    }
    printf("%d\n", ans);
}
