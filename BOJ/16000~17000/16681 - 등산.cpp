#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <queue>
#include <limits.h>
#include <vector>
#include <utility>
using namespace std;

int n, m, d, e;
int h[100001];

using lli = long long int;

vector<pair<int, lli>> g[100001];
priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> pq;
lli d1[100001], d2[100001];
bool isVisited[100001];

void process(lli*const& arr, int start)
{
	for(int i = 1; i <= n; i++) {
		arr[i] = LLONG_MAX;
		isVisited[i] = false;
	}
	while(pq.empty() == false) pq.pop();

	arr[start] = 0;
	pq.push({ 0, start });
	while(pq.empty() == false) {
		int current = start;
		while(1) {
			current = pq.top().second;
			pq.pop();
			if(isVisited[current] == false || pq.empty()) break;
		}
		if(isVisited[current] == true) break;

		isVisited[current] = true;

		for(auto t : g[current]) {
			int next = t.first;
			lli cost = t.second;
			if(isVisited[next] == true || h[current] >= h[next]) continue;

			if(arr[next] > arr[current] + cost) {
				arr[next] = arr[current] + cost;
				pq.push({ arr[next], next });
			}
		}
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d %d %d", &n, &m, &d, &e);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &h[i]);
	}
	for(int i = 0; i < m; i++) {
		int a, b, length;
		scanf("%d %d %d", &a, &b, &length);

		g[a].push_back({ b, length });
		g[b].push_back({ a, length });
	}

	process(d1, 1);
	process(d2, n);

	lli res = LLONG_MIN;
	for(int i = 2; i <= n - 1; i++) {
		if(d1[i] == LLONG_MAX || d2[i] == LLONG_MAX) continue;

		lli cost = h[i] * (lli)e - (d1[i] + d2[i]) * d;
		if(res < cost)
			res = cost;
	}

	if(res == LLONG_MIN) {
		printf("Impossible");
	} else {
		printf("%lld", res);
	}

	return 0;
}
