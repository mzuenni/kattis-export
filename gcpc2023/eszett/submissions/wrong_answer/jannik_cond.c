#include <stdio.h>

char s[22];

int main() {
	scanf("%s",s);
	for (int i = 0; s[i]; i++)
		s[i] = s[i] + 'a' - 'A';
	printf("%s\n",s);
	for (int p = 0; ; ) {
		if (!s[p] || !s[p+1]) break;
		while (s[p] && s[p+1] && (s[p] != 's' || s[p+1] != 's')) p++;
		if (s[p] == 's')
		{
			s[p] = '\0';
			printf("%sB%s\n", s, s + p + 2);
			s[p] = 's';
			p++;
		}
	}
	return 0;
}
