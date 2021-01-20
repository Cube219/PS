#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n;
char str[100005];
int d[100005];
int r[10000001];
int gap = 1000000;
int dd[100001];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %s", &n, str);
        for(int i = 0; i < n; i++) {
            d[i] = str[i] - '0';
            dd[i] = 0;
        }
        
        int current = 0;
        for(int i = 0; i < n; i++) {
            current += d[i] - 1;
            r[gap + current]++;
            dd[i] = gap + current;
        }

        lli res = 0;
        res += r[0];
        current = 0;
        for(int i = 0; i < n; i++) {
            res += r[gap + current];
            r[dd[i]]--;
            current += d[i];
            current--;
        }

        printf("%lld\n", res);
    }

    return 0;
}
