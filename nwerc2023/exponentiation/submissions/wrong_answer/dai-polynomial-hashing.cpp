#include <bits/stdc++.h>
using namespace std;

const int N = 3010;
int n, m, x, y;
char c;
long long arr[N][N];

int main() {
    scanf("%d %d ", &n, &m);
    memset(arr, 0, sizeof(arr));
    for (int i = 1; i <= n; i++) arr[i][0] = 1;
    while(m--)
    {
        scanf("%c %d %d ", &c, &x, &y);
        if (c == '!')
        {
            for (int i = 0; i < N-1; i++)
            {
                arr[x][i+1] += arr[y][i] + arr[x][i+1];
            }
        }
        else 
        {
        	bool printed = false;
            for (int i = N-1; i > 0; i--)
            {
                if (arr[x][i] > arr[y][i]) 
                {
                    printed = printf(">\n");
                    break;
                }
                else if (arr[x][i] < arr[y][i])
                {
                    printed = printf("<\n");
                    break;
                }
            }
            if(!printed) printf("=\n");
        }
    }
}