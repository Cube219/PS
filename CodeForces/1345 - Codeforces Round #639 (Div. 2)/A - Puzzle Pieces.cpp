#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &m);

        if(n == 1 || m == 1) {
            printf("YES\n");
            continue;
        }

        if(n == 2 && m == 2) {
            printf("YES\n");
            continue;
        }

        printf("NO\n");
        continue;
    }

    return 0;
}
