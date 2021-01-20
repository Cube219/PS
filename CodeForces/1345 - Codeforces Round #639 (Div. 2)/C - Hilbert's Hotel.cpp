#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, a;
int b[200001];
bool isPossible;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        isPossible = true;
        for(int i = 0; i < n; i++) {
            b[i] = 0;
        }

        for(int i = 0; i < n; i++) {
            scanf("%d", &a);
            a += i;
            a = a % n;
            if(a < 0)
                a += n;

            if(b[a] != 0) {
                isPossible = false;
            }
            b[a] = 1;
        }

        if(isPossible == true) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
