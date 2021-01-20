#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
using namespace std;

char a[1001], b[1001];
int al, bl;
int d[1001][1001], r[1001][1001];

char printBuf[1001];

int main(void)
{
	// freopen("input.txt", "r", stdin);

	scanf("%s %s", a, b);
	al = strlen(a);
	bl = strlen(b);

	for(int i = 1; i <= al; i++) {
		for(int j = 1; j <= bl; j++) {
			int res = -1, res2 = 0;
			if(res < d[i - 1][j]) {
				res = d[i - 1][j];
				res2 = 1;
			}
			if(res < d[i][j - 1]) {
				res = d[i][j - 1];
				res2 = 2;
			}

			if(a[i - 1] == b[j - 1]) {
				if(res < d[i - 1][j - 1] + 1) {
					res = d[i - 1][j - 1] + 1;
					res2 = 3;
				}
			}

			d[i][j] = res;
			r[i][j] = res2;
		}
	}

	printf("%d\n", d[al][bl]);
	if(d[al][bl] != 0) {
		int printL = d[al][bl];

		int x = al, y = bl, currentP = 0;
		while(x > 0 && y > 0) {
			switch(r[x][y])
			{
			case 1:
				x--;
				break;

			case 2:
				y--;
				break;

			case 3:
				printBuf[currentP++] = a[x - 1];
				x--;
				y--;
				break;

			default:
				break;
			}
		}

		for(int i = printL - 1; i >= 0; i--) {
			printf("%c", printBuf[i]);
		}
	}

	return 0;
}
