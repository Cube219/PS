#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>

int n, r1, r2, strSize;
char str[4001];
int idxToNode[4001], nodeToIdx[2001][2];

int parent[4001][50], depth[4001];

int st[4001];
int stTop;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %s %d %d", &n, str, &r1, &r2);
	strSize = n * 2;

	int currentNode = 0;
	st[stTop] = 0;
	for(int i = 0; i < strSize; i++) {
		int s = str[i] - '0';

		if(s == 0) {
			currentNode++;

			parent[currentNode][0] = st[stTop];
			depth[currentNode] = stTop + 1;

			st[++stTop] = currentNode;
			idxToNode[i + 1] = st[stTop];
			nodeToIdx[st[stTop]][0] = i + 1;
		} else {
			idxToNode[i + 1] = st[stTop];
			nodeToIdx[st[stTop]][1] = i + 1;
			stTop--;
		}
	}

	for(int i = 0; i < 20; i++) {
		for(int j = 1; j <= n; j++) {
			if(parent[j][i] != 0) {
				parent[j][i + 1] = parent[parent[j][i]][i];
			}
		}
	}

	int node1 = idxToNode[r1];
	int node2 = idxToNode[r2];

	if(depth[node1] > depth[node2]) {
		int t = node1;
		node1 = node2;
		node2 = t;
	}

	int diff = depth[node2] - depth[node1];
	for(int i = 0; diff > 0; i++) {
		if(diff % 2 == 1) node2 = parent[node2][i];
		diff /= 2;
	}

	if(node1 != node2) {
		for(int i = 19; i >= 0; i--) {
			if(parent[node1][i] != 0 && parent[node2][i] != 0 && parent[node1][i] != parent[node2][i]) {
				node1 = parent[node1][i];
				node2 = parent[node2][i];
			}
		}

		node1 = parent[node1][0];
	}

	printf("%d %d", nodeToIdx[node1][0], nodeToIdx[node1][1]);

	return 0;
}
