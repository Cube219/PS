#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m, x, y;
char d[101][1001];
int cost;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d %d", &n, &m, &x, &y);
        for(int i = 0; i < n; i++) {
            scanf("%s", &d[i]);
        }

        bool useY;
        if(x * 2 < y) useY = false;
        else useY = true;

        cost = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(d[i][j] == '.') {
                    if(useY == true && d[i][j+1] == '.' && j+1 < m) {
                        cost += y;
                        j++;
                    } else {
                        cost += x;
                    }
                }
            }
        }

        printf("%d\n", cost);
    }

    return 0;
}
