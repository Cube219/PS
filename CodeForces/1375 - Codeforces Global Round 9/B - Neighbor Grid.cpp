#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m, d[310][310], res[310][310];
bool isPossible;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        isPossible = true;

        scanf("%d %d", &n, &m);

        for(int i = 0; i <= n + 1; i++) {
            d[i][0] = d[i][m + 1] = 0;
            res[i][0] = res[i][m + 1] = 0;
        }
        for(int i = 0; i <= m + 1; i++) {
            d[0][i] = d[n + 1][i] = 0;
            res[0][i] = res[n + 1][i] = 0;
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                scanf("%d", &d[i][j]);
                res[i][j] = d[i][j];
            }
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(d[i][j] == 0) continue;

                int cnt = 0;
                if(d[i - 1][j] > 0) cnt++;
                if(d[i][j - 1] > 0) cnt++;
                if(d[i + 1][j] > 0) cnt++;
                if(d[i][j + 1] > 0) cnt++;

                if(d[i][j] > cnt) {
                    int plus = d[i][j] - cnt;
                    if(i > 1 && d[i - 1][j] == 0) {
                        res[i - 1][j] = 1;
                        plus--;
                        if(plus == 0) continue;
                    }
                    if(j > 1 && d[i][j - 1] == 0) {
                        res[i][j - 1] = 1;
                        plus--;
                        if(plus == 0) continue;
                    }
                    if(i < n && d[i + 1][j] == 0) {
                        res[i + 1][j] = 1;
                        plus--;
                        if(plus == 0) continue;
                    }
                    if(j < m && d[i][j + 1] == 0) {
                        res[i][j + 1] = 1;
                        plus--;
                        if(plus == 0) continue;
                    }

                    isPossible = false;
                    break;
                }
            }
            if(isPossible == false) break;
        }

        if(isPossible == false) {
            printf("NO\n");
            continue;
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(res[i][j] > 0) {
                    int cnt = 0;
                    if(res[i - 1][j] > 0) cnt++;
                    if(res[i][j - 1] > 0) cnt++;
                    if(res[i + 1][j] > 0) cnt++;
                    if(res[i][j + 1] > 0) cnt++;
                    
                    res[i][j] = cnt;
                }
            }
        }

        printf("YES\n");
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                printf("%d ", res[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
