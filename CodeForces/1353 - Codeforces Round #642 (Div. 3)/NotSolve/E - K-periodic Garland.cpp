#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, k;
char s[1000001];
int d[1000001];
int cnt;
int res;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %s", &n, &k, s);

        cnt = 0;
        for(int i = 0; i < n; i++) d[i] = 0;

        int lastOne = -1;
        for(int i = 0; i < n; i++) {
            if(s[i] == '1') {
                lastOne = i;
                break;
            }
        }
        if(lastOne == -1) {
            printf("0\n");
            continue;
        }
        for(int i = lastOne + 1; i < n; i++) {
            if(s[i] == '1') {
                d[i] = i - lastOne;
                lastOne = i;
            }
        }

        int last = 0;
        bool mustCombine = false;
        for(int i = 0; i < n; i++) {
            if(d[i] != 0) {
                if(mustCombine == true) {
                    d[i] += d[last];
                    mustCombine = false;
                    cnt++;
                }

                if(d[i] == k) {
                    continue;
                }
                else if(d[i] < k) {
                    last = i;
                    mustCombine = true;
                }
                else {
                    cnt += (d[i] - 1) / k;
                    d[i] = d[i] % k;

                    if(d[i] != 0) {
                        last = i;
                        mustCombine = true;
                    }
                }
            }
        }
        if(mustCombine == true)
            cnt++;

        res = cnt;

        printf("%d\n", cnt);
    }

    return 0;
}
