#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        int count = 0;

        while(n > 1) {
            count++;
            int currentN = 2, currentH = 1;
            while(n >= currentN + (currentH + 1) * 2 + currentH) {
                currentN += (currentH + 1) * 2 + currentH;

                currentH++;
            }
            n -= currentN;
        }

        printf("%d\n", count);
    }

    return 0;
}
