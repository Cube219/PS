#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int tNum;
int n;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        printf("%d\n", n / 2 + 1);
    }

    return 0;
}
