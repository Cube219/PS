#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <algorithm>
#include <stack>
#include <math.h>
using namespace std;

struct Dot
{
	int x;
	int y;
};

int n;
Dot d[100001];
Dot st[100001];
int stTop;

using lli = long long int;

lli isCCW(int x1, int y1, int x2, int y2)
{
	return (lli)(x1) * (lli)(y2) - (lli)(x2) * (lli)(y1);
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	Dot min;

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		d[i] = { x, y };
	}
	sort(d, d + n, [](const Dot& l, const Dot& r) {
		if(l.y < r.y) return true;
		else if(l.y == r.y && l.x < r.x) return true;
		else return false;
	});

	min = d[0];

	sort(d + 1, d + n, [min](const Dot& l, const Dot& r) {
		Dot lMin, rMin;
		lMin.x = l.x - min.x;
		lMin.y = l.y - min.y;
		rMin.x = r.x - min.x;
		rMin.y = r.y - min.y;

		lli a = (lli)(lMin.x) * (lli)(rMin.y);
		lli b = (lli)(lMin.y) * (lli)(rMin.x);
		if(a != b) return a > b;
		else if(lMin.y != rMin.y) return lMin.y < rMin.y;
		else return lMin.x < rMin.x;
	});

	st[0] = d[0];
	st[1] = d[1];
	stTop = 1;

	for(int i = 2; i < n; i++) {
		Dot d1 = st[stTop - 1];
		Dot d2 = st[stTop];
		Dot d3 = d[i];

		lli c = isCCW(d2.x - d1.x, d2.y - d1.y, d3.x - d1.x, d3.y - d1.y);
		if(c == 0) {
			st[stTop] = d3;
		} else if(c > 0) {
			st[++stTop] = d3;
		} else {
			stTop--;
			i--;
		}
	}


	printf("%d", stTop + 1);

	return 0;
}
