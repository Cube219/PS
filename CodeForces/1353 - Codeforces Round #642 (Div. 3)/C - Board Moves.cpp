#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum, n;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        long long int sum = 0;
        for(long long int i = 3; i <= n; i+=2) {
            sum += (i - 1) * 4 * (i / 2);
        }

        printf("%lld\n", sum);
    }

    return 0;
}
