#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>

int tNum;
int n;
char d[100];
int st[100], stTop;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %s", &n, d);

        stTop = -1;

        for(int i = 0; i < n; i++) {
            if(d[i] == '(') {
                st[++stTop] = i;
            } else {
                if(stTop >= 0) {
                    stTop--;
                }
            }
        }

        printf("%d\n", stTop + 1);
    }

    return 0;
}
