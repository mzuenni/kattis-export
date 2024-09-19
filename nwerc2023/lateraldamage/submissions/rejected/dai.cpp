// @EXPECTED_RESULTS@: RUN_TIME_ERROR, WRONG_ANSWER
#include <iostream>
using namespace std;

int n, k;
string x;

int main() {
    scanf("%d%d", &n, &k);
    k *= 5;
    for (int i = 0; i < n; i++)
    {
        for (int j = i%5; j < n; j+=5)
        {
            printf("%d %d\n", i+1, j+1);
            fflush(stdout);
            //cout << i+1 << ' ' << j+1 << endl;
            scanf("%s", &x);

            if (x == "miss") continue;
            k--;
            cerr << i+1 << ' ' << j+1 << ' ' << endl;
            for (int d = -4; d <= 4; d++)
            {
                if (d == 0) continue;
                
                if (i+d < 0 || i+d >= n) continue;
                //cout << i+d+1 << ' ' << j+1 << endl;
                cerr << i+d+1 << ' ' << j+1 << endl;
                printf("%d %d\n", i+d+1, j+1);
                fflush(stdout);
                scanf("%s", &x);
                if (x == "sunk") k--;
                if (!k) return 0;
                
                if (j+d < 0 || j+d >= n) continue;
                //cout << i+1 << ' ' << j+d+1 << endl;
                cerr << i+1 << ' ' << j+d+1 << endl;
                printf("%d %d\n", i+1, j+d+1);
                fflush(stdout);
                scanf("%s", &x);
                if (x == "sunk") k--;
                if (!k) return 0;
            }
        }
    }
    return 0;
}