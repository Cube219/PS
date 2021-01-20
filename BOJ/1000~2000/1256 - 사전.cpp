#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
using namespace std;

int n, m, k;
int d[202][202];
char buf[202];

int p(int l, int aCnt)
{
	// printf("$%d %d\n", l, aCnt);
	if(l < 1) return 0;
	if(aCnt == 0) return 1;
	if(d[l][aCnt] != 0) return d[l][aCnt];

	int a;
	if(aCnt > 0) {
		a = p(l - 1, aCnt - 1);
	} else {
		a = 0;
	}
	int notA;
	if(l - aCnt > 0) {
		notA = p(l - 1, aCnt);
	} else {
		notA = 0;
	}

	int sum = a + notA;
	if(sum > 1000000000) {
		sum = 1000000000;
	}

	d[l][aCnt] = sum;

	return sum;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &n, &m, &k);

	for(int i = 1; i <= n + m; i++) {
		d[i][0] = 1;
	}
	d[1][1] = 1;

	p(n + m, n);

	int aCnt = n, l = n + m;
	for(int i = 0; i < n + m - 1; i++) {
		if(k > d[l][aCnt]) {
			printf("-1");
			return 0;
		}

		if(k <= d[l - 1][aCnt - 1]) {
			buf[i] = 'a';
			l--;
			aCnt--;
		} else {
			buf[i] = 'z';
			k -= d[l - 1][aCnt - 1];
			l--;
		}
	}
	if(aCnt == 1) buf[n + m - 1] = 'a';
	else buf[n + m - 1] = 'z';

	printf("%s", buf);

	return 0;
}
