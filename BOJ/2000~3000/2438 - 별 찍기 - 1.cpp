#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= i; j++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
