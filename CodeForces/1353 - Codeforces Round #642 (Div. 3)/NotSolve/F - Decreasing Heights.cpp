#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m, a[101][101], d[101][101], current[101][101];

constexpr int IMAX = 2147483647;

int abs(int a)
{
    if(a < 0) return -a;
    else return a;
}

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &m);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }

        d[n-1][m-1] = 0;
        current[n-1][m-1] = a[n-1][m-1];

        for(int i = n - 1; i >= 0; i--) {
            for(int j = m - 1; j >= 0; j--) {
                if(current[i][j] != 0) continue;

                int down = IMAX, right = IMAX;
                int downCost = 0, rightCost = 0;
                if(i != n - 1) {
                    down = a[i][j] - current[i + 1][j];
                    downCost = d[i + 1][j];
                }

                if(j != m - 1) {
                    right = a[i][j] - current[i][j + 1];
                    rightCost = d[i][j + 1];
                }
                int downAbs = abs(down);
                int rightAbs = abs(right);
                if(downAbs + downCost < rightAbs + rightCost) {

                }
            }
        }
    }

    return 0;
}
