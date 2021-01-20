#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
using namespace std;

int a, b, c;

long long int p(int n, int r)
{
	if(r == 2)
		return ((long long int)n * n) % c;
	if(r == 1)
		return n % c;

	if(r % 2 == 1) {
		return (p(n, r / 2 + 1) * p(n, r / 2)) % c;
	} else {
		long long int t = p(n, r / 2);
		return (t * t) % c;
	}
}

int main(void)
{
	cin >> a >> b >> c;

	cout << p(a, b);

	return 0;
}
