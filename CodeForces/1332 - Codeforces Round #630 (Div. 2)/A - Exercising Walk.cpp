#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum, left, right, up, down;
int x, y, x1, y1, x2, y2;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d %d %d %d %d %d %d %d", &left, &right, &down, &up, &x, &y, &x1, &y1, &x2, &y2);

        if(x1 == x2 && (left > 0 || right > 0)) {
            printf("No\n");
            continue;
        }
        if(y1 == y2 && (up > 0 || down > 0)) {
            printf("No\n");
            continue;
        }

        int dX = right - left;
        int dY = up - down;

        x += dX;
        y += dY;

        if(x < x1 || x > x2 || y < y1 || y > y2) {
            printf("No\n");
            continue;
        }

        printf("Yes\n");
    }

    return 0;
}
