#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

using lli = long long int;

int n, m, k;
lli tree[3000002];
int leafStart;

constexpr lli MOD = 1000000007;

lli res(int l, int r, int node, int reqL, int reqR)
{
	if(r < reqL || l > reqR) return 1;
	if(l >= reqL && r <= reqR) return tree[node];

	int mid = (l + r) / 2;
	return (res(l, mid, node * 2, reqL, reqR) * res(mid + 1, r, node * 2 + 1, reqL, reqR)) % MOD;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d %d", &n, &m, &k);

	leafStart = 1;
	while(leafStart < n) {
		leafStart *= 2;
	}
	for(int i = 0; i < leafStart; i++) {
		tree[leafStart + i] = 1;
	}

	for(int i = 0; i < n; i++) {
		scanf("%lld", &tree[leafStart + i]);
	}
	for(int i = leafStart - 1; i >= 1; i--) {
		tree[i] = (tree[i * 2] * tree[i * 2 + 1]) % MOD;
	}

	for(int i = 0; i < m + k; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		if(a == 1) {
			int current = leafStart + b - 1;

			tree[current] = c;
			current /= 2;
			while(current > 0) {
				tree[current] = (tree[current * 2] * tree[current * 2 + 1]) % MOD;
				current /= 2;
			}
		} else {
			printf("%lld\n", res(1, leafStart, 1, b, c));
		}
	}

	return 0;
}
