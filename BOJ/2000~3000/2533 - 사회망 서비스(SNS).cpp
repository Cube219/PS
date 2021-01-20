#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
using namespace std;

int n;
vector<int> edges[1000001];
int visited[1000001];

int d[1000001][2];

int process(int i, bool isParentEA)
{
	if(d[i][isParentEA] != -1)
		return d[i][isParentEA];

	visited[i] = 1;
	// EA인 경우
	int ea = 1;
	for(auto n : edges[i]) {
		if(visited[n] != 1) {
			ea += process(n, true);
		}
	}

	// EA가 아닌 경우
	int nea = 2147483647;
	if(isParentEA == true) {
		nea = 0;
		for(auto n : edges[i]) {
			if(visited[n] != 1) {
				nea += process(n, false);
			}
		}
	}

	if(ea < nea) {
		d[i][isParentEA] = ea;
	} else {
		d[i][isParentEA] = nea;
	}

	visited[i] = 0;

	return d[i][isParentEA];
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);

		edges[u].push_back(v);
		edges[v].push_back(u);
	}

	for(int i = 0; i <= n; i++) {
		d[i][0] = d[i][1] = -1;
	}

	printf("%d", process(1, true));

	return 0;
}
