#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
using namespace std;

using lli = long long int;

int n, m;
int parent[100001][18];
int depth[100001];
vector<int> g[100001];

void makeTree(int node, int dep)
{
	depth[node] = dep;
	for(auto child : g[node]) {
		if(depth[child] == 0) {
			parent[child][0] = node;
			makeTree(child, dep + 1);
		}
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}

	makeTree(1, 1);

	for(int i = 0; i < 17; i++) {
		for(int j = 1; j <= n; j++) {
			if(parent[j][i] != 0) {
				parent[j][i + 1] = parent[parent[j][i]][i];
			}
		}
	}

	scanf("%d", &m);
	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		if(depth[a] > depth[b]) {
			int t = a;
			a = b;
			b = t;
		}

		int gap = depth[b] - depth[a];

		int idx = 0;
		while(gap > 0) {
			if(gap % 2 == 1) {
				b = parent[b][idx];
			}
			idx++;
			gap /= 2;
		}

		if(a != b) {
			for(int j = 17; j >= 0; j--) {
				if(parent[a][j] != 0 && parent[b][j] != 0 && parent[a][j] != parent[b][j]) {
					a = parent[a][j];
					b = parent[b][j];
				}
			}

			a = parent[a][0];
		}

		printf("%d\n", a);
	}


	return 0;
}
