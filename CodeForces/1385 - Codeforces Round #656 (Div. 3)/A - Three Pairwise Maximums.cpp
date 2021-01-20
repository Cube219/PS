#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <algorithm>

int tNum;
int d[3];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d", &d[0], &d[1], &d[2]);

        std::sort(d, d + 3);

        if(d[0] != d[1] && d[1] != d[2] && d[0] != d[2]) {
            printf("NO\n");
            continue;
        }

        if(d[1] != d[2]) {
            printf("NO\n");
        } else {

            printf("YES\n%d %d %d\n", d[0], d[0], d[2]);
        }
    }

    return 0;
}
