#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int tNum;
int n;
int sn[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

long long int d[101][101];

long long int pow(int a, int b)
{
    long long int r = 1;
    for(int i = 0; i < b; i++) {
        r *= a;
    }
    return r;
}

long long int p(int l, int remain)
{
    if(l == 0 && remain == 0) return 0;
    if(l == 0 && remain != 0) return -1;
    if(remain < 2) return -1;
    if(l <= 0) return -1;

    if(d[l][remain] != 0) return d[l][remain];

    if(l == 1) {
        for(int i = 0; i < 10; i++) {
            if(sn[i] == remain) {
                d[l][remain] = i;
                return i;
            }
        }
        d[l][remain] = -1;
        return -1;
    }

    for(int i = 0; i < 10; i++) {
        long long int res = p(l - 1, remain - sn[i]);
        if(res != -1) {
            res += i * pow(10, l-1);
            d[l][remain] = res;
            return res;
        }
    }

    d[l][remain] = -1;
    return -1;
}

void printWithZero(long long int v, int l)
{
    char buf[100];

    for(int i = 0; i < l; i++) {
        buf[i] = (v % 10) + '0';
        v = v / 10;
    }
    for(int i = l - 1; i >= 0; i--) {
        printf("%c", buf[i]);
    }
    printf(" ");
}

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        int length;
        bool isFinished = false;
        for(length = 1; length <= 100; length++) {
            for(int i = 1; i <= 9; i++) {
                long long int res = p(length - 1, n - sn[i]);
                if(res == -1) continue;

                printf("%d", i);
                printWithZero(res, length - 1);

                isFinished = true;
                break;
            }

            if(isFinished == true) break;
        }

        if(n % 2 == 1) {
            printf("7");
            n -= 3;
        }
        while(n > 0) {
            printf("1");
            n -= 2;
        }
        printf("\n");
    }

    return 0;
}
