#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

using lli = long long int;

lli n, m, k;
// lli d[1000001];
lli t[3000002];
int leafStart;

lli Sum(int left, int right, int node, int rLeft, int rRight)
{
	if(right < rLeft || left > rRight) return 0;
	if(left >= rLeft && right <= rRight) return t[node];
	int mid = (left + right) / 2;
	return Sum(left, mid, node * 2, rLeft, rRight) + Sum(mid + 1, right, node * 2 + 1, rLeft, rRight);
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%lld %lld %lld", &n, &m, &k);
	
	leafStart = 1;
	while(leafStart < n) {
		leafStart *= 2;
	}

	for(int i = 0; i < n; i++) {
		scanf("%lld", &t[leafStart + i]);
	}

	for(int i = leafStart - 1; i >= 1; i--) {
		t[i] = t[i * 2] + t[i * 2 + 1];
	}

	for(int i = 0; i < m + k; i++) {
		lli a, b, c;
		scanf("%lld %lld %lld", &a, &b, &c);

		if(a == 1) { // Change
			int current = leafStart + b - 1;
			lli delta = c - t[current];
			while(current > 0) {
				t[current] += delta;
				current /= 2;
			}
		} else { // Sum
			printf("%lld\n", Sum(1, leafStart, 1, b, c));
		}
	}

	return 0;
}
