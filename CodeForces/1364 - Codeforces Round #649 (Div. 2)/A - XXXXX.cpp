#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, x, a[100001];
int sum, l, r;

int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        sum = 0;

        scanf("%d %d", &n, &x);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            
            sum += a[i];
        }

        if(sum % x != 0) {
            printf("%d\n", n);
            continue;
        }

        l = -1;
        for(int i = 0; i < n; i++) {
            if(a[i] % x != 0) {
                l = i;
                break;
            }
        }
        r = n;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] % x != 0) {
                r = i;
                break;
            }
        }

        if(l == -1) {
            printf("-1\n");
            continue;
        }

        if(l < n - r) {
            res = n - l - 1;
        } else {
            res = r;
        }

        printf("%d\n", res);
    }

    return 0;
}
