#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, m, k;
int max1, max2;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d", &n, &m, &k);

        max1 = max2 = -1;

        int cp = n / k;
        if(cp >= m) {
            printf("%d\n", m);
            continue;
        } else {
            max1 = cp;
            max2 = (m - cp) / (k - 1);
            if((m - cp) % (k - 1) != 0) max2++;
            printf("%d\n", max1 - max2);
        }
    }

    return 0;
}
