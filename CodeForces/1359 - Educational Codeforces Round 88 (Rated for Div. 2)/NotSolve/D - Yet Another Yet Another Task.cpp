#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int n, a[100001], d[100001], mx[100001];
int res = -987654321;

int main(void)
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int aa;
        scanf("%d", &a[i]);
    }
    d[0] = a[0];
    mx[0] = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] + d[i - 1] < a[i]) {
            d[i] = a[i];
            mx[i] = a[i];
        } else {
            d[i] = a[i] + d[i - 1];
            if(mx[i - 1] < a[i]) {
                mx[i] = a[i];
            } else {
                mx[i] = mx[i - 1];
            }
        }
        if(res < d[i] - mx[i]) {
            res = d[i] - mx[i];
        }
    }
    
    if(n == 1) {
        res = 0;
    }

    printf("%d", res);

    return 0;
}
