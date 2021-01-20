#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, m;
int d[1000001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n;

	int dMax = -1;
	for(int i = 0; i < n; i++) {
		cin >> d[i];
		if(dMax < d[i]) dMax = d[i];
	}
	cin >> m;

	int l = 0, h = dMax+1;
	while(l + 1 < h) {
		int mid = (l + h) / 2;

		long long int sum = 0;
		for(int i = 0; i < n; i++) {
			if(mid > d[i])
				sum += d[i];
			else
				sum += mid;
		}

		if(sum <= m)
			l = mid;
		else
			h = mid;
	}

	cout << l;

	return 0;
}
