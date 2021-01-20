#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int n, a, b;

int main(void)
{
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);

        int t = a / b;
        t++;

        printf("%d\n", ((t*b) - a) % b);
    }

    return 0;
}