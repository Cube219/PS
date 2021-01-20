#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m;
int d[102][102];

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &m);

        int currentBW = 1;
        for(int i = 1; i <= n; i++) {
            if(i % 2 == 1) currentBW = 1;
            else currentBW = 2;

            for(int j = 1; j <= m; j++) {
                d[i][j] = currentBW;
                
                if(currentBW == 1) currentBW = 2;
                else currentBW = 1;
            }
        }

        if((n * m) % 2 != 1) {
            if(d[1][1] == 2)
                d[1][1] = 1;
            else if(d[1][m] == 2)
                d[1][m] = 1;
            else if(d[n][1] == 2)
                d[n][1] = 1;
            else if(d[n][m] == 2)
                d[n][1] = 1;
        }

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(d[i][j] == 1) printf("%c", 'B');
                else printf("%c", 'W');
            }
            printf("\n");
        }
    }

    return 0;
}
