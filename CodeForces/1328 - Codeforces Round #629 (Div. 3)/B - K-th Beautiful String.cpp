#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tcase, n, k;

int main(void)
{
    scanf("%d", &tcase);
    for(int tt = 0; tt < tcase; tt++) {
        scanf("%d %d", &n, &k);

        int firstB = 1;
        for(int i = 1; i < 100000; i++) {
            if(k - i <= 0) break;
            k -= i;
            firstB++;
        }

        int secondB = k - 1;

        for(int i = n-1; i >= 0; i--) {
            if(i == firstB || i == secondB)
                printf("b");
            else
                printf("a");
        }
        printf("\n");
    }

    return 0;
}