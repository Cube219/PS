#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
using namespace std;

int n;
long long int k;
long long int d[51][51];
char buf[51];

long long int pow(long long int a, long long int b)
{
	long long int res = 1;
	for(int i = 0; i < b; i++) {
		res *= a;
	}
	return res;
}

long long int p(int l, int leftCount)
{
	if(leftCount < 0) return pow(2, l);
	if(d[l][leftCount] != 0) return d[l][leftCount];

	// (
	long long int t = 0;
	if(leftCount >= 0) {
		t = p(l - 1, leftCount + 1);
	}
	else {
		t = pow(2, l - 1);
	}

	// )
	long long int t2 = 0;
	if(leftCount >= 0) {
		t2 = p(l - 1, leftCount - 1);
	}
	else {
		t2 = pow(2, l - 1);
	}

	long long int res = t + t2;
	// if(res > 2147483647) res = 2147483647;
	d[l][leftCount] = res;

	return res;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d %lld", &n, &k);
	k++;

	for(int i = 0; i <= 50; i++) {
		d[0][i] = 1;
		d[1][i] = 2;
	}
	d[1][1] = 1;

	p(n, 0);

	int currentLeftCount = 0;
	for(int i = 0; i < n; i++) {
		int l = n - i;

		if(currentLeftCount < 0) {
			long long int leftCount = pow(2, l - 1);
			if(leftCount >= k) {
				buf[i] = '(';
			}
			else {
				buf[i] = ')';
				k -= leftCount;
			}

			continue;
		}

		long long int leftCount = p(l - 1, currentLeftCount + 1);

		if(leftCount >= k) {
			buf[i] = '(';
			currentLeftCount++;
		}
		else {
			buf[i] = ')';
			k -= leftCount;
			currentLeftCount--;
		}
	}

	if(k > 1) {
		printf("-1");
	}
	else {
		printf("%s", buf);
	}

	return 0;
}
