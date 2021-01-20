#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int n, w[10001];
vector<int> g[10001];
int d[100001][2]; // 0: 미포함, 1: 포함
int r[100001][2]; // 해당 값이 포함되나
int c[100001];

int printBuf[100001];
int printL;

int process(int node, bool isParentSelected)
{
	if(d[node][isParentSelected] != 0)
		return d[node][isParentSelected];

	c[node] = 1;

	int res = -1, notInclude = 0, include = 0, hasChild = false;
	// 본인을 미포함
	for(auto childNode : g[node]) {
		if(c[childNode] != 1) {
			notInclude += process(childNode, false);
			hasChild = true;
		}
	}

	// 본인을 포함
	if(isParentSelected == false) {
		for(auto childNode : g[node]) {
			if(c[childNode] != 1) {
				include += process(childNode, true);
			}
		}
		include += w[node];
	}

	if(hasChild == true) {
		res = notInclude;
		r[node][isParentSelected] = false;

		if(res < include) {
			res = include;
			r[node][isParentSelected] = true;
		}
	} else {
		if(isParentSelected == false) {
			res = w[node];
			r[node][isParentSelected] = true;
		} else {
			res = 0;
			r[node][isParentSelected] = false;
		}
	}

	d[node][isParentSelected] = res;

	c[node] = 0;

	return res;
}

void track(int node, bool isParentSelected)
{
	if(r[node][isParentSelected] == true)
		printBuf[printL++] = node;

	c[node] = 1;

	for(auto child : g[node]) {
		if(c[child] != 1)
			track(child, r[node][isParentSelected]);
	}

	c[node] = 0;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
	}
	for(int i = 0; i < n - 1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}

	g[0].push_back(1);

	int res = process(0, false);
	printf("%d\n", res);

	if(res != 0) {
		track(0, false);
		sort(printBuf, printBuf + printL);
		
		for(int i = 0; i < printL; i++) {
			printf("%d ", printBuf[i]);
		}
	}

	return 0;
}
