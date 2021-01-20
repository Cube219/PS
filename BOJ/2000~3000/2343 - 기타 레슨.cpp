#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, m;
int d[100001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	int dSum = 0;
	cin >> n >> m;
	for(int i = 0; i < n; i++) {
		cin >> d[i];
		dSum += d[i];
	}

	int l = 0, h = dSum;
	while(l + 1 < h) {
		int mid = (l + h) / 2;

		int cnt = 0, currentSum = 0;
		bool isPossible = true;
		for(int i = 0; i < n; i++) {
			if(cnt >= m) {
				isPossible = false;
				break;
			}
			if(currentSum + d[i] > mid) {
				cnt++;
				currentSum = 0;
				i--;
				continue;
			}

			currentSum += d[i];
		}

		if(isPossible == true) {
			h = mid;
		} else {
			l = mid;
		}
	}

	cout << h;

	return 0;
}
