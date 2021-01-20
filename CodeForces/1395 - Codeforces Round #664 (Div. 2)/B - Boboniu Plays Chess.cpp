#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int n, m, sx, sy;
bool isVisited[101][101];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &sx, &sy);

    int cx = sx, cy = sy;
    isVisited[cx][cy] = true;

    printf("%d %d\n", cx, cy);

    cy = 1;
    isVisited[cx][cy] = true;

    printf("%d %d\n", cx, cy);

    for(int i = 2; i <= m; i++) {
        cy = i;
        if(isVisited[cx][cy] == true) continue;
        isVisited[cx][cy] = true;
        printf("%d %d\n", cx, cy);
    }

    for(int i = 1; i <= n; i++) {
        cx = i;
        if(isVisited[cx][cy] == true) continue;

        if(cy == m) {
            while(cy >= 1) {
                isVisited[cx][cy] = true;
                printf("%d %d\n", cx, cy);
                cy--;
            }
            cy++;
        } else {
            while(cy <= m) {
                isVisited[cx][cy] = true;
                printf("%d %d\n", cx, cy);
                cy++;
            }
            cy--;
        }
    }

    return 0;
}
