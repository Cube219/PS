#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

using lli = long long int;

int n, q;

lli tree[300001];
int startIndex;

lli p(int currentL, int currentR, int l, int r, int node)
{
	if(currentR < l || currentL > r) return 0;
	if(l <= currentL && currentR <= r) return tree[node];

	int m = (currentL + currentR) / 2;
	return p(currentL, m, l, r, node * 2) + p(m + 1, currentR, l, r, node * 2 + 1);
}

int main(void)
{
	// freopen("input.txt", "r", stdin);
	scanf("%d %d", &n, &q);

	startIndex = 1;
	while(startIndex < n) startIndex *= 2;

	for(int i = 0; i < n; i++) {
		int index = startIndex + i;
		int a;
		scanf("%d", &a);
		
		while(index > 0) {
			tree[index] += a;
			index /= 2;
		}
	}

	for(int i = 0; i < q; i++) {
		int x, y, a;
		lli b;
		scanf("%d %d %d %lld", &x, &y, &a, &b);
		if(x > y) {
			int t = x;
			x = y;
			y = t;
		}
		x--;
		y--;

		printf("%lld\n", p(0, startIndex - 1, x, y, 1));
		
		int index = startIndex + a - 1;
		lli old = tree[index];
		while(index > 0) {
			tree[index] -= old;
			tree[index] += b;
			index /= 2;
		}
	}

	return 0;
}
