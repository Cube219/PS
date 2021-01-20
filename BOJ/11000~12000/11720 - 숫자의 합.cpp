#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int n;
	cin >> n;
	getchar();

	int res = 0;

	for(int i = 0; i < n; i++) {
		char c = getchar();
		res += c - '0';
	}

	cout << res;

	return 0;
}
