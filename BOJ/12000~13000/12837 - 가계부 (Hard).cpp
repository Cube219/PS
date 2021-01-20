#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

using lli = long long int;

int n, q;

lli tree[3000001];
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

	for(int i = 0; i < q; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		
		if(a == 1) {
			int index = startIndex + b - 1;
			while(index > 0) {
				tree[index] += c;
				index /= 2;
			}
		} else {
			printf("%lld\n", p(1, startIndex, b, c, 1));
		}
	}

	return 0;
}
