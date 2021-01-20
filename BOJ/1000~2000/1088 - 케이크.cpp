#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <float.h>
#include <tuple>
using namespace std;

using node = tuple<double, int, int>;

priority_queue<node> maxPQ;
int n, m;
double currentMin, res;
int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);

	int a;
	scanf("%d", &a);
	currentMin = a;
	maxPQ.push({ a, a, 1 });

	for(int i = 1; i < n; i++) {
		scanf("%d", &a);
		if(currentMin > a) currentMin = a;
		maxPQ.push({ a, a, 1 });
	}
	scanf("%d", &m);

	double topValue;
	int topOriginal;
	int topCount;
	tie(topValue, topOriginal, topCount) = maxPQ.top();
	res = topValue - currentMin;

	for(int i = 0; i < m; i++) {
		tie(topValue, topOriginal, topCount) = maxPQ.top();
		maxPQ.pop();

		topCount++;
		topValue = (double)topOriginal / (double)topCount;
		if(topValue < currentMin) currentMin = topValue;
		maxPQ.push({ topValue, topOriginal, topCount });

		tie(topValue, topOriginal, topCount) = maxPQ.top();
		if(res > topValue - currentMin) {
			res = topValue - currentMin;
		}
	}

	printf("%.16f", res);

	return 0;
}
