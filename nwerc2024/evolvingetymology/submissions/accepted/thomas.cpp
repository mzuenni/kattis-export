// Author: Thomas Beuman

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int NMAX = 100000;

char s[NMAX+1];
bool Seen[NMAX];
char ans[NMAX+1];

int main()
{
	int n;
	long long k;
	scanf("%d %lld %s", &n, &k, s);
	int m = 1;
	while (n % 2 == 0 && k > 0) {
		n /= 2;
		m *= 2;
		k--;
	}
	if (k == 0) {
		for (int i = 0; i < n; i++)
			ans[i] = s[m*i];
	}
	else {
		memset(Seen, false, sizeof(Seen));
		for (int i = 0; i < n; i++)
			if (!Seen[i]) {
				vector<int> Cycle;
				int j = i;
				while (true) {
					Seen[j] = true;
					Cycle.push_back(j);
					j = (2*j) % n;
					if (j == i)
						break;
				}
				int nc = Cycle.size();
				for (int j = 0; j < nc; j++)
					ans[Cycle[j]] = s[m*Cycle[(j+k)%nc]];
			}
	}
	ans[n] = '\0';
	for (int i = 0; i < m; i++)
		printf("%s", ans);
	printf("\n");
	return 0;
}
