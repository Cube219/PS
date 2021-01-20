#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, k;

int findDivisor(int odd)
{
    for(int i = 3; i <= odd; i++) {
        if(odd % i == 0)
            return i;
    }
}

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &k);

        if(n % 2 == 0) {
            n += 2 * k;
        } else {
            int div = findDivisor(n);

            n += div;

            n += 2 * (k - 1);
        }

        printf("%d\n", n);
    }

    return 0;
}
