#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, s[100001], d[100001];
int max;

int main(void)
{
   freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &s[i]);
            d[i] = 1;
        }

        max = 1;

        d[1] = 1;
        for(int i = 1; i <= n; i++) {
            for(int j = i + i; j <= n; j += i) {
                if(s[i] < s[j]) {
                    if(d[j] < d[i] + 1) {
                        d[j] = d[i] + 1;
                        if(d[j] > max) max = d[j];
                    }
                }
            }
        }

        printf("%d\n", max);
    }

    return 0;
}
