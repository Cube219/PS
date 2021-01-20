#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m, x;
int min, max;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d", &n, &x, &m);

        min = max = x;
        for(int i = 0; i < m; i++) {
            int l, r;
            scanf("%d %d", &l, &r);

            if(r < min || l > max) continue;

            if(l < min) min = l;
            if(r > max) max = r;
        }

        printf("%d\n", max - min + 1);
    }

    return 0;
}
