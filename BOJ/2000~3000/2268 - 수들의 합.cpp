#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

using lli = long long int;

int n, m;
lli tree[3000001];
int startIndex;

lli p(int currentL, int currentR, int l, int r, int node)
{
	if(currentR < l || r < currentL) return 0;
	if(l <= currentL && currentR <= r) return tree[node];

	int m = (currentL + currentR) / 2;
	return p(currentL, m, l, r, node * 2) + p(m + 1, currentR, l, r, node * 2 + 1);
}

int main(void)
{
	// freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &m);

	startIndex = 1;
	while(startIndex < n) {
		startIndex *= 2;
	}

	for(int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		if(a == 0) {
			if(b > c) {
				int t = b;
				b = c;
				c = t;
			}

			printf("%lld\n", p(0, startIndex - 1, b - 1, c - 1, 1));
		} else {
			int index = startIndex + b - 1;
			lli old = tree[index];
			while(index > 0) {
				tree[index] -= old;
				tree[index] += c;
				index /= 2;
			}
		}
	}

	return 0;
}
