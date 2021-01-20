#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
	int n, x;
	scanf("%d %d", &n, &x);

	for(int i = 0; i < n; i++) {
		int t;
		scanf("%d", &t);

		if(t < x)
			printf("%d ", t);
	}

	return 0;
}
