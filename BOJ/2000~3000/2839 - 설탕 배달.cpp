#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int d[5001] = { 0, 99999, 99999, 1, 99999, 1, };

int main(void)
{
	int n;
	cin >> n;

	if(n < 5) {
		if(d[n] >= 99999)
			cout << "-1";
		else
			cout << d[n];
		return 0;
	}

	for(int i = 6; i <= n; i++) {
		if(d[i - 3] < d[i - 5])
			d[i] = d[i - 3] + 1;
		else
			d[i] = d[i -5] + 1;
	}

	if(d[n] >= 99999)
		cout << "-1";
	else
		cout << d[n];

	return 0;
}
