#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
using namespace std;

int n, m, k;
int d[11][220][221];

int p(int length, int start, int remain)
{
	if(remain <= 0) return 0;
	if(start * length > remain) return 0;
	if(length == 1) {
		if(start <= remain) {
			d[length][start][remain] = 1;
			return 1;
		} else {
			return 0;
		}
	}

	if(d[length][start][remain] != 0) return d[length][start][remain];

	int res = 0;
	for(int i = start; i <= remain; i++) {
		res += p(length - 1, i, remain - i);
	}

	d[length][start][remain] = res;
	return res;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &n, &m, &k);
	p(n, 1, m);

	int start = 1, length = n, remain = m;
	for(int i = 0; i < n - 1; i++) {
		for(int j = start; j <= remain; j++) {
			int t = p(length - 1, j, remain - j);

			if(k <= t) {
				printf("%d ", j);
				length--;
				remain -= j;
				start = j;
				break;
			} else {
				k -= t;
			}
		}
	}
	printf("%d", remain);

	return 0;
}
