#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, m;
int d[1000001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	int maxD = -1;
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> d[i];
		if(maxD < d[i])
			maxD = d[i];
	}

	int l = 0, h = maxD;
	while(l +1 < h) {
		int mid = (l + h) / 2;

		long long int sum = 0;
		for(int i = 0; i < n; i++) {
			if(d[i] - mid > 0)
				sum += d[i] - mid;
		}

		if(sum >= m)
			l = mid;
		else
			h = mid;
	}

	cout << l;

	return 0;
}
