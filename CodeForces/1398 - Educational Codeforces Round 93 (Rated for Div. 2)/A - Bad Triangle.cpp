#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n, a[50001];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);

        int c = a[n - 1];
        int aa = a[0] + a[1];
        if(c >= aa) printf("1 2 %d\n", n);
        else printf("-1\n");
    }

    return 0;
}
