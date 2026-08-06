// @EXPECTED_RESULTS@: WRONG-ANSWER
#include <cstdio>

using namespace std;

int main(){
	int n;
	char c[4];
	char a[4];
	scanf("%d", &n);
	for(;n--;){
		scanf("%s %s %s %s", &c[0], &c[1], &c[2], &c[3]);
		c[0] -= 'A';
		c[1] -= '1';
		c[2] -= 'A';
		c[3] -= '1';
		a[0] = c[0] + c[1];
		a[1] = c[0] - c[1];
		a[2] = c[2] + c[3];
		a[3] = c[2] - c[3];
		printf("1000");
		for(int i=0; i<1000; ++i){
			printf(" %c %c", c[0] + 'A' + (i%2), c[1] + '1' + (i%2));
		}
		puts("");
	}
}
