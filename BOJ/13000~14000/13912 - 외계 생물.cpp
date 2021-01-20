#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
using namespace std;

using lli = long long int;

int n;
lli d[101];

constexpr lli MOD = 1000000007;

int twoPow(int n)
{
	int res = 1;
	for(int i = 0; i < n; i++) res *= 2;
	return res;
}

lli mul(lli a, lli b)
{
	lli res = 1;
	while(b > 0) {
		if(b % 2 == 1) {
			res = (res * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}

	return res;
}

lli com(lli a, lli b)
{
	lli top = 1, bot = 1;

	for(lli i = a; i >= a - b + 1; i--) {
		top = (top * i) % MOD;
	}
	for(lli i = b; i >= 2; i--) {
		bot = (bot * i) % MOD;
	}
	lli res = (top * mul(bot, MOD-2)) % MOD;
	return res;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	d[1] = 1;
	for(int i = 2; i <= n + 1; i++) {
		int m = twoPow(i) - 2;
		d[i] = (((d[i - 1] * d[i - 1]) % MOD) * com(m, m/2)) % MOD;
	}

	printf("%lld", d[n + 1]);

	return 0;
}
