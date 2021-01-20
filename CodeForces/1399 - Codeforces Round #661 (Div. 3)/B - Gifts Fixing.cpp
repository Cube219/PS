#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int tNum;
int n, a[51], b[51];
int aMin, bMin;
lli res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        aMin = 2147483647;
        bMin = 2147483647;
        res = 0;

        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if(aMin > a[i]) aMin = a[i];
        }
        for(int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
            if(bMin > b[i]) bMin = b[i];
        }

        for(int i = 0; i < n; i++) {
            lli eatA = a[i] - aMin;
            lli eatB = b[i] - bMin;

            if(eatA < eatB) res += eatB;
            else res += eatA;
        }

        printf("%lld\n", res);
    }

    return 0;
}
