#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <algorithm>

using lli = long long int;

int n, m, y11, y22;
int top[100001], bot[100001], tmp[100001];

int botLeft[100001], botRight[100001], topLeft[100001], topRight[100001];
lli res;

constexpr lli MOD = 1000000007;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d %d %d", &n, &m, &y11, &y22);
	for(int i = 0; i < n; i++) {
		scanf("%d", &top[i]);
	}
	for(int i = 0; i < m; i++) {
		scanf("%d", &bot[i]);
	}

	std::sort(top, top + n);
	std::sort(bot, bot + m);

	int topIdx, botIdx;
	// topRight '\'
	topIdx = botIdx = 0;
	while(topIdx < n && botIdx < m) {
		if(top[topIdx] >= bot[botIdx]) {
			botIdx++;
			continue;
		} else {
			topRight[topIdx] = m - botIdx;
			topIdx++;
		}
	}
	// topLeft '/'
	topIdx = n - 1;
	botIdx = m - 1;
	while(topIdx >= 0 && botIdx >= 0) {
		if(top[topIdx] <= bot[botIdx]) {
			botIdx--;
			continue;
		} else {
			topLeft[topIdx] = botIdx + 1;
			topIdx--;
		}
	}
	// botRight '/'
	topIdx = botIdx = 0;
	while(topIdx < n && botIdx < m) {
		if(top[topIdx] <= bot[botIdx]) {
			topIdx++;
			continue;
		} else {
			botRight[botIdx] = n - topIdx;
			botIdx++;
		}
	}
	// botLeft '\'
	topIdx = n - 1;
	botIdx = m - 1;
	while(topIdx >= 0 && botIdx >= 0) {
		if(top[topIdx] >= bot[botIdx]) {
			topIdx--;
			continue;
		} else {
			botLeft[botIdx] = topIdx + 1;
			botIdx--;
		}
	}

	lli topRightSum = 0;
	for(int i = 0; i < n; i++) {
		topRightSum += topRight[i];
	}
	topRightSum -= topRight[0];
	for(int i = 0; i < n - 1; i++) {
		res = (res + ((topLeft[i] * topRightSum) % MOD)) % MOD;

		topRightSum -= topRight[i + 1];
	}

	lli botRightSum = 0;
	for(int i = 0; i < m; i++) {
		botRightSum += botRight[i];
	}
	botRightSum -= botRight[0];
	for(int i = 0; i < m - 1; i++) {
		res = (res + ((botLeft[i] * botRightSum) % MOD)) % MOD;

		botRightSum -= botRight[i + 1];
	}

	printf("%lld", res);

	return 0;
}
