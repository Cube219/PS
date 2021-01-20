#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
using namespace std;

long long int k;
long long int d[200][2];

long long int p(int l, bool isParentOne)
{
	if(l == 0) return 1;
	if(d[l][isParentOne] != 0) return d[l][isParentOne];

	if(l == 1) {
		int r = 0;
		if(isParentOne == true) r = 1;
		else r = 2;
		d[l][isParentOne] = r;
		return r;
	}

	long long int r = 0;
	// 0인 경우
	r = p(l - 1, false);

	// 1인 경우
	if(isParentOne == false) {
		r += p(l - 1, true);
	}

	d[l][isParentOne] = r;

	return r;
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%lld", &k);

	int length = 1;
	//long long int ck = 0;
	while(1) {
		long long int r = p(length - 1, true);
		if(k <= r) break;

		k -= r;
		length++;
	}

	bool isParentOne = true;
	printf("1");
	for(int i = 1; i < length; i++) {
		if(isParentOne == true) {
			printf("0");
			isParentOne = false;
			continue;
		}

		long long int r = p(length - i - 1, false);

		if(k <= r) {
			printf("0");
		} else {
			printf("1");
			k -= r;
			isParentOne = true;
		}
	}

	return 0;
}
