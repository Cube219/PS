#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int tNum;
int r, g, b, w;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %d %d", &r, &g, &b, &w);

        int eNum = 0;
        bool hasZero = false;
        if(r % 2 == 0) eNum++;
        if(g % 2 == 0) eNum++;
        if(b % 2 == 0) eNum++;
        if(r == 0) hasZero = true;
        if(g == 0) hasZero = true;
        if(b == 0) hasZero = true;

        bool we;
        if(w % 2 == 0) we = true;
        else we = false;

        if(eNum == 3) {
            printf("Yes\n");
            continue;
        }
        if(eNum == 2 && we == true) {
            printf("Yes\n");
            continue;
        }

        if(hasZero == true) {
            printf("No\n");
            continue;
        }
        eNum = 3 - eNum;
        if(we == true) we = false;
        else we = true;
        if(eNum == 3) {
            printf("Yes\n");
            continue;
        }
        if(eNum == 2 && we == true) {
            printf("Yes\n");
            continue;
        }
        printf("No\n");
    }

    return 0;
}
