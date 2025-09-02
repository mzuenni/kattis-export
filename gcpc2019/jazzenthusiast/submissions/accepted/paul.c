#include <stdio.h>

int main() {
	int n, c, m, s;
	scanf("%d%d", &n, &c);
	int t = (1-n)*c;
	while (n--) {
		scanf("%d:%d", &m, &s);
		t += 60*m+s;
	}
	printf("%02d:%02d:%02d\n", t/60/60, t/60%60, t%60);
}
