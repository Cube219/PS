#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, d[200001];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        res = 0;

        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &d[i]);
        }

        int s = 1, e = n;
        for(int i = 1; i <= n; i++) {
            if(d[i] != i) break;
            s++;
        }
        for(int i = n; i >= 1; i--) {
            if(d[i] != i) break;
            e--;
        }
        if(s > n) {
            printf("0\n");
            continue;
        }

        int diff = 0;
        for(int i = s; i <= e; i++) {
            if(d[i] != i) diff++;
        }
        if(diff == e - s + 1) {
            printf("1\n");
        } else {
            printf("2\n");
        }
    }

    return 0;
}
