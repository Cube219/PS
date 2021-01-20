#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int a, b;
	cin >> a >> b;

	printf("%.9f", (double)a / b);

	return 0;
}
