#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, a;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        int zeroCount = 0, oneCount = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a);

            if(i % 2 == a % 2) continue;

            if(i % 2 == 0 && a % 2 == 1) {
                zeroCount++;
            } else if(i % 2 == 1 && a % 2 == 0) {
                oneCount++;
            }
        }

        if(zeroCount == 0 && oneCount == 0) printf("0\n");
        else if(zeroCount == oneCount) printf("%d\n", zeroCount);
        else printf("-1\n");
    }

    return 0;
}
