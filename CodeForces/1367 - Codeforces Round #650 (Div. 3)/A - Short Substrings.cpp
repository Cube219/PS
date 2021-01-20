#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

int tNum;
char d[101];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%s", d);

        int l = strlen(d);

        for(int i = 0; i < l; i += 2) {
            printf("%c", d[i]);
        }
        printf("%c\n", d[l - 1]);
    }

    return 0;
}
