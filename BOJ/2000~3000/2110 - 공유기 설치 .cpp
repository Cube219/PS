#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

int n, c;
int d[200001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n >> c;
	int dMax = 0;
	for(int i = 0; i < n; i++) {
		cin >> d[i];
		if(dMax < d[i])
			dMax = d[i];
	}

	sort(d, d + n);

	int l = 0, h = d[n-1];
	while(l + 1 < h) {
		int mid = (l + h) / 2;

		int cnt = 0, lastX = -1000000000;
		for(int i = 0; i < n; i++) {
			if(d[i] - lastX >= mid) {
				cnt++;
				lastX = d[i];
			}
		}

		if(cnt >= c) {
			l = mid;
		} else {
			h = mid;
		}
	}

	cout << l;

	return 0;
}
