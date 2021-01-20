#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, a[101];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if(a[i] < 0) a[i] = -a[i];
        }

        for(int i = 0; i < n; i += 2) {
            a[i] = -a[i];
        }

        for(int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    return 0;
}
