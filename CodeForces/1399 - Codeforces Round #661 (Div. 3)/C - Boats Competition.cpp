#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int tNum;
int n, d[51];
int res;
bool isUsed[51];

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        res = 0;

        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &d[i]);

        for(int s = 2; s <= 100; s++) {
            int cnt = 0;
            for(int i = 0; i < n; i++) isUsed[i] = false;

            for(int i = 0; i < n; i++) {
                if(isUsed[i] == true) continue;

                for(int j = i + 1; j < n; j++) {
                    if(isUsed[j] == true) continue;

                    if(d[i] + d[j] == s) {
                        cnt++;
                        isUsed[i] = true;
                        isUsed[j] = true;
                        break;
                    }
                }
            }
            if(res < cnt) res = cnt;
        }

        printf("%d\n", res);
    }

    return 0;
}
