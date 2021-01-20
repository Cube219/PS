#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
using namespace std;

int main(void)
{
	int n;
	cin >> n;

	for(int i = n; i >= 1; i--) {
		for(int j = 1; j <= i; j++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
