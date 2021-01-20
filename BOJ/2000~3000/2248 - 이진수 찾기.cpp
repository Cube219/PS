#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
using namespace std;

int nn, nNum;
unsigned int nTh;

unsigned int d[32][32];

char res[33];

int process(int n, int nNum)
{
	if(d[n][nNum] != 0) return d[n][nNum];
	if(n == 0 || nNum == 0) {
		d[n][nNum] = 1;
		return 1;
	}

	int res = process(n - 1, nNum);
	if(nNum > 0) res += process(n - 1, nNum - 1);

	d[n][nNum] = res;

	return res;
}

void process2(int n, int nNum, unsigned int remain, int resIndex)
{
	if(n == 0) return;
	if(nNum == 0) {
		for(int i = resIndex; i < nn; i++) {
			res[i] = '0';
		}
		res[nn] = '\0';
		return;
	}

	unsigned int zeroCase = d[n - 1][nNum];

	if(remain > zeroCase) {
		res[resIndex] = '1';
		process2(n - 1, nNum - 1, remain - zeroCase, resIndex + 1);
	} else {
		res[resIndex] = '0';
		process2(n - 1, nNum, remain, resIndex + 1);
	}
}

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%d  %d %d", &nn, &nNum, &nTh);

	process(nn, nNum);

	process2(nn, nNum, nTh, 0);

	printf("%s", res);

	return 0;
}
