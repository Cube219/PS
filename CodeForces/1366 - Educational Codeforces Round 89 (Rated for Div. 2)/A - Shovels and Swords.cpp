#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int a, b;
int count;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &a, &b);

        if(a > b) {
            int t = a;
            a = b;
            b = t;
        }

        int res = 0;

        if(a < b / 2) {
            res = a;
            a = 0;
            b -= res * 2;
        } else {
            res = b / 2;
            a -= res;
            b = b % 2;

            count = res;

            if(b == 1 && a >= 2) {
                res++;
                b--;
                a -= 2;
            }

            int temp = a / 3;
            if(count >= temp) res += temp;
            else res += count;
        }

        printf("%d\n", res);
    }

    return 0;
}
