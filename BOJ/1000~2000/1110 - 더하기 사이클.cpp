#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int n, count = 0, old;
	cin >> n;

	old = n;

	do {
		int a, b;
		a = n / 10;
		b = n % 10;

		n = b * 10 + ((a+b)%10);
		count++;
	} while(old != n);

	cout << count;

	return 0;
}
