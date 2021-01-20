#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <algorithm>
#include <utility>

int n, a[1000001];
int tree[3000002];
std::pair<int, int> ai[1000001];
int startIndex;
int res;

int GetValue(int currentL, int currentR, int l, int r, int node)
{
	if(currentR < l || currentL > r) return 0;
	if(l <= currentL && r >= currentR) return tree[node];

	int m = (currentL + currentR) / 2;
	int v1 = GetValue(currentL, m, l, r, node * 2);
	int v2 = GetValue(m + 1, currentR, l, r, node * 2 + 1);
	if(v1 > v2) return v1;
	else return v2;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		ai[i] = { a[i], i };
	}

	startIndex = 1;
	while(startIndex < n) {
		startIndex *= 2;
	}

	std::sort(ai, ai + n, [](const std::pair<int, int>& l, const std::pair<int, int>& r) {
		if(l.first < r.first) return true;
		if(l.first == r.first && l.second > r.second) return true;
		return false;
	});

	for(int i = 0; i < n; i++) {

		int currentIndex = ai[i].second;

		int v = GetValue(0, startIndex - 1, 0, currentIndex - 1, 1);
		v++;
		if(res < v) res = v;

		int i2 = startIndex + currentIndex;
		while(i2 > 0) {
			if(tree[i2] < v) {
				tree[i2] = v;
			}
			i2 /= 2;
		}
	}

	printf("%d", res);

	return 0;
}
