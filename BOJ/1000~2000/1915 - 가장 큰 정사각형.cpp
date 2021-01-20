#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using namespace std;

int n, m;
char map[1001][1001];
int d[1001][1001];

int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%s", map[i]);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            d[i][j] = map[i - 1][j - 1] - '0';
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(d[i][j] == 0) continue;

            int dd = d[i - 1][j - 1];
            if(dd > d[i - 1][j]) dd = d[i - 1][j];
            if(dd > d[i][j - 1]) dd = d[i][j - 1];
            
            d[i][j] = dd + 1;

            if(res < d[i][j]) res = d[i][j];
        }
    }

    printf("%d", res * res);

    return 0;
}
