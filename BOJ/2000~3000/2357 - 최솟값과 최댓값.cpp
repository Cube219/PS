#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int n, m, d[100001];
int minTree[300001], maxTree[300001];
int startIndex;

int findMin(int currentL, int currentR, int l, int r, int node)
{
	if(currentR < l || currentL > r) return 1000000001;
	if(l <= currentL && currentR <= r) return minTree[node];

	int m = (currentL + currentR) / 2;
	int v1 = findMin(currentL, m, l, r, node * 2);
	int v2 = findMin(m + 1, currentR, l, r, node * 2 + 1);
	
	if(v1 < v2) return v1;
	else return v2;
}

int findMax(int currentL, int currentR, int l, int r, int node)
{
	if(currentR < l || currentL > r) return 0;
	if(l <= currentL && currentR <= r) return maxTree[node];

	int m = (currentL + currentR) / 2;
	int v1 = findMax(currentL, m, l, r, node * 2);
	int v2 = findMax(m + 1, currentR, l, r, node * 2 + 1);

	if(v1 > v2) return v1;
	else return v2;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		scanf("%d", &d[i]);
	}

	startIndex = 1;
	while(startIndex < n) startIndex *= 2;
	for(int i = 1; i <= startIndex * 2; i++) {
		minTree[i] = 1000000001;
	}

	for(int i = 0; i < n; i++) {
		int index = startIndex + i;
		
		while(index > 0) {
			if(minTree[index] > d[i]) minTree[index] = d[i];
			if(maxTree[index] < d[i]) maxTree[index] = d[i];

			index /= 2;
		}
	}

	for(int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		b--;

		printf("%d %d\n", findMin(0, startIndex - 1, a, b, 1), findMax(0, startIndex - 1, a, b, 1));
	}

	return 0;
}
