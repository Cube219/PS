#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int a1[10001], a2[10001];
char buf[10001];
int d[10001][10];
int r[10001][10];

int p(int pos, int offset)
{
	if(pos >= n) return 0;

	if(offset > 9) offset -= 10;
	if(d[pos][offset] != 0) return d[pos][offset];

	int plusCount = 0, minusCount = 0;

	// Plus Count
	int current = a1[pos] + offset;
	if(current > 9) {
		current -= 10;
	}
	while(current != a2[pos]) {
		plusCount++;
		current++;
		if(current > 9) current -= 10;
	}

	// Minus Count
	current = a1[pos] + offset;
	if(current > 9) {
		current -= 10;
	}
	while(current != a2[pos]) {
		minusCount++;
		current--;
		if(current < 0) current += 10;
	}

	int t = minusCount + p(pos + 1, offset);
	int t2 = plusCount + p(pos + 1, offset + plusCount);

	if(t < t2) {
		d[pos][offset] = t;
		r[pos][offset] = -minusCount;
		return t;
	} else {
		d[pos][offset] = t2;
		r[pos][offset] = plusCount;
		return t2;
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d", &n);
	scanf("%s", buf);
	for(int i = 0; i < n; i++) {
		a1[i] = buf[i] - '0';
	}
	scanf("%s", buf);
	for(int i = 0; i < n; i++) {
		a2[i] = buf[i] - '0';
	}

	int t = p(0, 0);

	printf("%d\n", t);
	int currentOffset = 0;
	for(int i = 0; i < n; i++) {
		printf("%d %d\n", i+1, r[i][currentOffset]);
		if(r[i][currentOffset] > 0) {
			currentOffset += r[i][currentOffset];

			if(currentOffset > 9) currentOffset -= 10;
		}
	}

	return 0;
}
