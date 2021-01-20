#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
using namespace std;

using lli = long long int;

int a, b, c, d, e, f;

int main(void)
{
	// freopen("input.txt", "r", stdin);

 	scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	int det = a * e - b * d;

	int x = (e*c-b*f) / det;
	int y = (-d*c+a*f) / det;

	printf("%d %d", x, y);

	return 0;
}
