#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

int n, a[200001], d[200001];
int count;

int main(void)
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    d[0] = 1;
    long long int sum;
    for(int i = 1; i < n; i++) {
        printf("%d", i);
        sum = 0;
        for(int j = i-1; j >= 0; j--) {
            sum += a[j];
        }
    }

    printf("%d", 0);

    return 0;
}
