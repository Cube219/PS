#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

using lli = long long int;

int tNum;
int n;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) printf("1 ");
            else printf("3 ");
        }
        printf("\n");
    }

    return 0;
}
