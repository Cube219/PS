#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <algorithm>

int tNum;
int n, a[1001];
int c[1001][1001], cNum;
int res[1001];

bool isGCD(int a, int b)
{
    if(a > b) std::swap(a, b);

    while(1) {
        int n = a % b;
        if(n == 0) {
            if(b != 1) return true;
            else return false;
        }

        a = b;
        b = n;
    }
}

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        cNum = 0;
        for(int i = 0; i < 1000; i++) {
            c[i][0] = -1;
        }

        scanf("%d", &n);

        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);

            int color = -1;
            for(int j = 0; j < cNum; j++) {
                int isValid = true;
                int k = 0;
                while(c[j][k] != -1) {
                    if(!isGCD(c[j][k], a[i])) {
                        isValid = false;
                        break;
                    }
                    k++;
                }

                if(isValid == true) {
                    c[j][k] = a[i];
                    c[j][k + 1] = -1;
                    color = j;
                    break;
                }
            }

            if(color == -1) {
                c[cNum][0] = a[i];
                c[cNum++][1] = -1;
                color = cNum;
            }
            res[i] = cNum;
        }

        printf("%d\n", cNum);
        for(int i = 0; i < n; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
    }

    return 0;
}
