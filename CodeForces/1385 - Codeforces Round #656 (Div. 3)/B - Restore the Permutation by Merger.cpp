#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, d[101];
int num[101];
int res[101];
int resNum;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n * 2; i++) {
            scanf("%d", &d[i]);
            num[i + 1] = 0;
        }

        resNum = 0;
        for(int i = 0; i < n * 2; i++) {
            num[d[i]]++;
            if(num[d[i]] == 2) {
                res[resNum++] = d[i];
            }
        }

        for(int i = 0; i < n; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
    }

    return 0;
}
