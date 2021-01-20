#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, k;
long long int d[10001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> k >> n;
	long long int dMax = 0;
	for(int i = 0; i < k; i++) {
		cin >> d[i];
		if(dMax < d[i])
			dMax = d[i];
	}

	long long int l = 0, h = dMax+1;
	while(l + 1 < h) {
		long long int mid = (l + h) / 2;

		long long int cnt = 0;
		for(int i = 0; i < k; i++) {
			cnt += d[i] / mid;
		}

		if(cnt >= n)
			l = mid;
		else
			h = mid;
	}

	cout << l;

	return 0;
}
