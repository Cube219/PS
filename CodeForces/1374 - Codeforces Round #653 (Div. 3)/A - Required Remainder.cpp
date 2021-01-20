#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int x, y, n;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d", &x, &y, &n);

        int k = n % x;

        if(k < y) {
            n -= (k + x - y);
        } else if(k > y) {
            n -= (k - y);
        }
        
        printf("%d\n", n);
    }

    return 0;
}
