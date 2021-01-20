#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

using lli = long long int;

int tNum;
int n, m, s, e;
vector<pair<int, int>> g[501];

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[501];
bool isVisited[501];
bool isImpossible;
vector<pair<int, int>> edgesToDelete;

int dfsBuf[501];

void DFS(int current, int l)
{
	if(current == e) {
		dfsBuf[l] = e;

		int a = dfsBuf[0];
		for(int i = 1; i <= l; i++) {
			int b = dfsBuf[i];
			edgesToDelete.push_back({ a, b });
			a = b;
		}
	}

	isVisited[current] = true;
	dfsBuf[l] = current;

	for(auto t : g[current]) {
		int next = t.first;
		int cost = t.second;

		if(isVisited[next] == true) continue;
		if(d[current] + cost == d[next]) {
			DFS(next, l + 1);
		}
	}

	isVisited[current] = false;
}

void process()
{
	isImpossible = false;
	while(pq.empty() == false) pq.pop();

	for(int i = 0; i < n; i++) {
		d[i] = 2147483647;
		isVisited[i] = false;
	}

	d[s] = 0;
	pq.push({ 0, s });
	while(pq.empty() == false) {
		int current = s;
		while(1) {
			current = pq.top().second;
			pq.pop();
			if(isVisited[current] == false || pq.empty()) break;
		}
		if(isVisited[current] == true) break;

		isVisited[current] = true;

		for(auto t : g[current]) {
			int next = t.first;
			int cost = t.second;
			if(isVisited[next] == true) continue;

			if(d[next] > d[current] + cost) {
				d[next] = d[current] + cost;
				pq.push({ d[next], next });
			}
		}
	}

	if(isVisited[e] == false) {
		isImpossible = true;
		return;
	}

	for(int i = 0; i < n; i++) isVisited[i] = false;
	DFS(s, 0);

	for(auto t : edgesToDelete) {
		int a = t.first;
		int b = t.second;

		auto findIter = find_if(g[a].begin(), g[a].end(), [b](const pair<int, int>& node) { return node.first == b; });
		if(findIter != g[a].end()) g[a].erase(findIter);
	}
	edgesToDelete.clear();
}

void process2()
{
	for(int i = 0; i < n; i++) {
		d[i] = 2147483647;
		isVisited[i] = false;
	}
	while(pq.empty() == false) pq.pop();

	if(isImpossible == true) return;

	d[s] = 0;
	pq.push({ 0, s });
	while(pq.empty() == false) {
		int current = s;
		while(1) {
			current = pq.top().second;
			pq.pop();
			if(isVisited[current] == false || pq.empty()) break;
		}
		if(isVisited[current] == true) break;

		isVisited[current] = true;
		if(current == e) break;

		for(auto t : g[current]) {
			int next = t.first;
			int cost = t.second;
			if(isVisited[next] == true) continue;

			if(d[next] > d[current] + cost) {
				d[next] = d[current] + cost;
				pq.push({ d[next], next });
			}
		}
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	while(1) {
		scanf("%d %d", &n, &m);
		if(n == 0 && m == 0) break;
		scanf("%d %d", &s, &e);

		for(int i = 0; i < n; i++) {
			g[i].clear();
		}

		for(int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			g[a].push_back({ b, c });
		}

		process();
		process2();

		if(d[e] == 2147483647) d[e] = -1;
		printf("%d\n", d[e]);
	}

	return 0;
}
