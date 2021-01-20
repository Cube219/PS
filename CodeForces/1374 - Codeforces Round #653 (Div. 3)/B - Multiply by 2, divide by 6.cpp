#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, twoNum, threeNum;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        threeNum = twoNum = 0;

        while(n % 3 == 0) {
            threeNum++;
            n /= 3;
        }
        while(n % 2 == 0) {
            twoNum++;
            n /= 2;
        }
        if(n != 1 || twoNum > threeNum) {
            printf("-1\n");
            continue;
        }

        printf("%d\n", threeNum + (threeNum - twoNum));
    }

    return 0;
}
