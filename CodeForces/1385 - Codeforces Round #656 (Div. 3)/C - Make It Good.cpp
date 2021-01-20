#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, d[200002];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &d[i]);
        }

        bool isDec = false;
        d[n] = -1;
        int i;
        for(i = n - 1; i >= 0; i--) {
            if(d[i] < d[i + 1]) {
                break;
            }
        }
        for(; i >= 0; i--) {
            if(d[i] > d[i + 1]) {
                break;
            }
        }

        printf("%d\n", i + 1);

    }

    return 0;
}
