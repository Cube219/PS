#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
using namespace std;

using lli = long long int;

int n, a[300001], b[300001], c[300001];

bool isBreaked[1000001];
int res;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
	}

	for(int i = 0; i < n; i++) {
		bool remained = true;
		if(isBreaked[a[i]] == true) remained = false;
		if(isBreaked[b[i]] == true) remained = false;
		if(isBreaked[c[i]] == true) remained = false;

		if(remained == true) {
			res++;
		}
		isBreaked[a[i]] = true;
		isBreaked[b[i]] = true;
		isBreaked[c[i]] = true;
	}

	printf("%d", res);

	return 0;
}
