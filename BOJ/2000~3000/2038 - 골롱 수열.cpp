#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <queue>
using namespace std;

using lli = long long int;

lli n;

struct Range
{
	lli st;
	lli ed;
	lli v;
};

queue<Range> qu;
lli res;

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%lld", &n);

	if(n == 1) {
		printf("1");
		return 0;
	} else if(n == 2 || n == 3) {
		printf("2");
		return 0;
	}
	
	qu.push({ 3, 3, 2 });
	lli current = 4;
	while(1) {
		Range r = qu.front();
		qu.pop();

		for(lli i = r.st; i <= r.ed; i++) {
			qu.push({ current, current + r.v - 1, i });
			current += r.v;

			if(current >= n + 1) {
				res = i;
				break;
			}
		}
		if(current >= n + 1) break;
	}

	printf("%lld", res);

	return 0;
}
