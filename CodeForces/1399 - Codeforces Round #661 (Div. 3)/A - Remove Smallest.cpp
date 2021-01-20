#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <algorithm>
#include <utility>

using lli = long long int;

int tNum;
int n, d[51];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        for(int i = 0; i < n; i++) {
            scanf("%d", &d[i]);
        }

        std::sort(d, d + n);
        bool isPossible = true;
        for(int i = 1; i < n; i++) {
            if(d[i - 1] + 1 < d[i]) {
                isPossible = false;
                break;
            }
        }

        if(isPossible == true) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
