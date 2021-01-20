#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

using lli = long long int;

int n;
int d[10001][2];
lli res;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);

	if(n == 1) {
		d[0][0] = 1;
		d[0][1] = 2;
		res = 2;
	} else {
		int current = n * 2;

		d[0][0] = current--;
		d[n - 1][0] = current--;
		d[0][1] = current--;
		d[n - 1][1] = current--;
		for(int i = n - 2; i >= 1; i--) {
			d[i][1] = current--;
		}
		for(int i = n - 2; i >= 1; i--) {
			d[i][0] = current--;
		}

		int n2 = n * 2;

		lli currentSum = (lli)n2 * (n2 + 1) / 2;
		lli t = 0;

		int insideNum = n2 - 4;

		for(int i = n2 - 3; i >= insideNum/2 + 1; i--) {
			currentSum -= i;

			t++;
			res += t * currentSum;
		}

		currentSum -= (lli)(n2 - 2);
		t++;
		res += t * currentSum;

		currentSum -= (lli)(n2 - 1);
		t++;
		res += t * currentSum;

		for(int i = insideNum/2; i >= 1; i--) {
			currentSum -= i;

			t++;
			res += t * currentSum;
		}
	}

	printf("%lld\n", res);
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < n; j++) {
			printf("%d ", d[j][i]);
		}
		printf("\n");
	}

	return 0;
}
