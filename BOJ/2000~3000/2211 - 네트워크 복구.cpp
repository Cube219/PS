#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

int n, m;

vector<pair<int, int>> g[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[1001];
bool isVisited[1001];
int r[1001];
pair<int, int> pr[1001];
int prNum;

void process()
{
	for(int i = 1; i <= n; i++) {
		d[i] = 2147483647;
	}
	d[1] = 0;
	pq.push({ 0, 1 });
	while(pq.empty() == false) {
		int current = 1;
		while(1) {
			current = pq.top().second;
			pq.pop();
			if(isVisited[current] == false || pq.empty()) break;
		}
		if(isVisited[current] == true) break;

		isVisited[current] = true;
		if(current != 1) {
			pr[prNum++] = { r[current], current };
		}

		for(auto t : g[current]) {
			int next = t.first;
			int cost = t.second;

			if(d[next] > d[current] + cost) {
				d[next] = d[current] + cost;
				pq.push({ d[next], next });
				r[next] = current;
			}
		}
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		g[a].push_back({ b, c });
		g[b].push_back({ a, c });
	}

	process();

	printf("%d\n", prNum);
	for(int i = 0; i < prNum; i++) {
		printf("%d %d\n", pr[i].first, pr[i].second);
	}

	return 0;
}
