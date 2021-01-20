#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

float sx, sy, ex, ey;
float canonX[101], canonY[101];
int n;

vector<pair<int, float>> g[201];
priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
float d[201];
bool isVisited[201];

float distanceSq(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

void process()
{
	for(int i = 0; i < n + 2; i++) {
		d[i] = FLT_MAX;
	}
	d[0] = 0.0f;
	pq.push({ 0.0f, 0 });
	while(pq.empty() == false) {
		int current = 0;
		while(1) {
			current = pq.top().second;
			pq.pop();
			if(isVisited[current] == false || pq.empty()) break;
		}
		if(isVisited[current] == true) break;

		isVisited[current] = true;
		for(auto t : g[current]) {
			int next = t.first;
			float cost = t.second;
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

	scanf("%f %f %f %f %d", &sx, &sy, &ex, &ey, &n);
	for(int i = 0; i < n; i++) {
		scanf("%f %f", &canonX[i], &canonY[i]);
	}

	// s(0) => e(1)
	g[0].push_back({ 1, distanceSq(sx, sy, ex, ey) / 5.0f });
	// s => each cannon
	for(int i = 0; i < n; i++) {
		g[0].push_back({ i + 2, distanceSq(sx, sy, canonX[i], canonY[i]) / 5.0f });
	}
	// each canon => e
	for(int i = 0; i < n; i++) {
		float dist = distanceSq(ex, ey, canonX[i], canonY[i]);
		g[i + 2].push_back({ 1, 2 + fabsf(dist - 50.0f) / 5.0f });
	}
	// each canon => each canon
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) continue;

			float dist = distanceSq(canonX[i], canonY[i], canonX[j], canonY[j]);
			g[i + 2].push_back({ j + 2, 2 + fabsf(dist - 50.0f) / 5.0f });
			g[j + 2].push_back({ i + 2, 2 + fabsf(dist - 50.0f) / 5.0f });
		}
	}

	process();

	printf("%.6f", d[1]);

	return 0;
}
