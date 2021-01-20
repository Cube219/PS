#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &m);

        if(n == 1) printf("0\n");
        else if(n == 2) printf("%d\n", m);
        else printf("%d\n", m * 2);
    }

    return 0;
}
