#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <utility>

using namespace std;

using lli = long long int;

int n;
char mv[300001];
int mvL;

lli firstNum[300001];

lli res;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d %s", &n, &mvL, mv);

    lli sum = 1;
    for(int i = 1; i <= n; i++) {
        firstNum[i] = sum;
        sum += i;
    }
    for(int i = n - 1; i >= 1; i--) {
        firstNum[n + n - i] = sum;
        sum += i;
    }

    int x = 1, y = 1;
    for(int i = 0; i < mvL; i++) {
        switch(mv[i]) {
            case 'U': x--; break;
            case 'D': x++; break;
            case 'L': y--; break;
            case 'R': y++; break;
            default:       break;
        }

        int digTh = x + y - 1;

        lli num;
        if(digTh % 2 == 0) { // 위에서 아래
            if(digTh <= n) {
                num = firstNum[digTh] + (lli)x - 1;
            } else {
                num = firstNum[digTh] + (lli)(n - y);
            }
            
        } else { // 아래에서 위
            if(digTh <= n) {
                num = firstNum[digTh] + (lli)y - 1;
            } else {
                num = firstNum[digTh] + (lli)(n - x);
            }
        }
        // printf("%lld\n", num);
        res += num;
    }

    printf("%lld", res + 1);

    return 0;
}
