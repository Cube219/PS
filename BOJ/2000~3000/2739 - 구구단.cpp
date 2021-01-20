#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int n;
	cin >> n;

	for(int i = 1; i <= 9; i++) {
		cout << n << " * " << i << " = " << n * i << endl;
	}

	return 0;
}
