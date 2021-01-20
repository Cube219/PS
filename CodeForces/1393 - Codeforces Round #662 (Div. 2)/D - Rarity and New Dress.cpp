#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int n, m;
char map[2001][2001];
int d[2001][2001];

int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", map[i]);
    }

    for(char f = 'a'; f <= 'z'; f++) {
        int cRes = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                d[i][j] = 0;
            }
        }

        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n; i++) {
                if(map[i][j] != f) continue;

                if(i <= 0 || j <= 1) d[i][j] = 1;
                else {
                    int minV = d[i - 1][j - 1];
                    if(minV > d[i][j - 2]) minV = d[i][j - 2];
                    if(minV > d[i + 1][j - 1]) minV = d[i + 1][j - 1];

                    if(map[i][j - 1] != f) d[i][j] = 1;
                    else d[i][j] = minV + 1;
                }

                cRes += d[i][j];
            }
        }

        res += cRes;
    }

    printf("%d", res);

    return 0;
}
