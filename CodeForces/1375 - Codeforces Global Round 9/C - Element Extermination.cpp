#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, a[300001];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        if(a[0] < a[n - 1]) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
