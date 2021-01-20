#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <math.h>

int tNum;
int n;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        int min = -1;
        int sq = sqrt(n);
        for(int i = 2; i <= sq; i++) {
            if(n % i == 0) {
                min = i;
                break;
            }
        }
        if(min == -1) {
            min = n;
        }
        printf("%d %d\n", n / min, n / min * (min - 1));
    }

    return 0;
}
