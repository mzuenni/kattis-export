#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct point { int x, y; };

i64 turn(point a, point b, point c) {
	return i64(b.x-a.x)*(c.y-a.y) - i64(b.y-a.y)*(c.x-a.x);
}

const int N = 1e6 + 10;
point lower[N], upper[N], result[N];
int lh = 0, lt = 1, uh = 0, ut = 1, rt = 0;

void add_gate(int x, int ymin, int ymax) {
	lower[lt++] = {x,ymin};
	while (lt-lh > 2 && turn(lower[lt-3], lower[lt-2], lower[lt-1]) >= 0) {
		lt--, lower[lt-1] = lower[lt];
	}
	upper[ut++] = {x,ymax};
	while (ut-uh > 2 && turn(upper[ut-3], upper[ut-2], upper[ut-1]) <= 0) {
		ut--, upper[ut-1] = upper[ut];
	}
	
	while (turn(lower[lh], lower[lh+1], upper[uh+1]) <= 0) {
		result[rt++] = lower[lh];
		if (lt-lh > 2) {
			upper[uh] = lower[++lh];
		} else if (ut-uh > 2) {
			lower[lh] = upper[++uh];
		} else {
			break;
		}
	}
}

int main() {
	point a, b;
	scanf("%d %d %d %d", &a.x, &a.y, &b.x, &b.y);

	lower[0] = upper[0] = a;
	
	int n;
	scanf("%d", &n);

	while (n--) {
		int x, ymin, ymax;
		scanf("%d %d %d", &x, &ymin, &ymax);
		add_gate(x, ymin, ymax);
	}	
	
	add_gate(b.x, b.y, b.y);
	result[rt++] = b;

	for (int i = 0; i < rt; i++) {
		printf("%d %d\n", result[i].x, result[i].y);
	}
}
