#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, m;
int d[100001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n >> m;
	int dSum = 0;
	for(int i = 0; i < n; i++) {
		cin >> d[i];
		dSum += d[i];
	}

	int l = 0, h = dSum;
	while(l + 1 < h) {
		int mid = (l + h) / 2;

		int remain = mid, cnt = 0;
		bool isPossible = true;
		for(int i = 0; i < n; i++) {
			if(cnt >= m) {
				isPossible = false;
				break;
			}

			if(remain - d[i] < 0) {
				cnt++;
				remain = mid;
				i--;
				continue;
			}

			remain -= d[i];
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
