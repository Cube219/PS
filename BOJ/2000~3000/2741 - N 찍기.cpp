#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
using namespace std;

int main(void)
{
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		printf("%d\n", i + 1);
	}

	return 0;
}
