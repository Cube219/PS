#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int cnt[10];

int main(void)
{
	int a, b, c;
	cin >> a >> b >> c;

	int s = a * b*c;

	while(s != 0) {
		cnt[s % 10]++;

		s /= 10;
	}

	for(int i = 0; i <= 9; i++) {
		cout << cnt[i] << endl;
	}

	return 0;
}
