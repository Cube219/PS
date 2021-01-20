#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
using namespace std;

using lli = long long int;

int n, m, k;

int main(void)
{
	// freopen("input.txt", "r", stdin);

 	scanf("%d %d %d", &n, &k, &m);
	m--;
	k--;

	int res = 0;

	while(1) {
		res++;
		int out = k % n;

		if(m == out) break;

		if(m < out) {
			m = n - (out - m) - 1;
		} else {
			m = m - out - 1;
		}
		n--;
	}

	printf("%d", res);

	return 0;
}
