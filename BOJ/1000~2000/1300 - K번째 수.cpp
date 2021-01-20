#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n, k;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	cin >> n >> k;

	long long int l = 0, h = (long long int)n * n;
	while(l + 1 < h) {
		long long int mid = (l + h) / 2;
		long long int cnt = 0;
		for(int i = 1; i <= n; i++) {
			long long c = mid / i;
			if(c < n)
				cnt += c;
			else
				cnt += n;
		}

		if(cnt == k) {
			h = mid;
			//break;
		} else if(cnt > k) {
			h = mid;
		} else {
			l = mid;
		}
	}

	cout << h;

	return 0;
}
