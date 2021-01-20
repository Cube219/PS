#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int n;
long long int a[100001];
long long int answer = -1;

long long int p(int s, int e)
{
	if(s == e)
		return (long long int)a[s];

	long long int leftRes = p(s, (s+e) / 2);
	long long int rightRes = p((s+e) / 2 + 1, e);

	long long int res;
	if(leftRes > rightRes) {
		res = leftRes;
	} else {
		res = rightRes;
	}

	int l, r;
	l = (s+e) / 2;
	r = (s+e) / 2 + 1;
	long long int cSum, cMin;
	cSum = 2;
	if(a[l] <= a[r]) {
		cMin = a[l];
	} else {
		cMin = a[r];
	}

	while(r-l <= e-s) {
		if(cSum * cMin > res) {
			res = cSum * cMin;
		}

		long long int rValue, lValue;
		if(r + 1 <= e) {
			rValue = a[r + 1];
		} else {
			rValue = -1;
		}
		if(l - 1 >= s) {
			lValue = a[l - 1];
		} else {
			lValue = -1;
		}

		if(lValue < rValue) {
			cSum++;
			if(cMin > rValue)
				cMin = rValue;
			r++;
		} else {
			cSum++;
			if(cMin > lValue)
				cMin = lValue;
			l--;
		}
	}

	return res;
}

int main(void)
{
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}

	answer = p(0, n - 1);

	cout << answer;

	return 0;
}
