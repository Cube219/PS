#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, k;
char d[200001];
int a[200001], aNum;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d %s", &n, &k, d);

        aNum = 0;
        
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(d[i] == '1') {
                a[aNum++] = cnt;
                cnt = 0;
            } else {
                cnt++;
            }
        }
        a[aNum++] = cnt;

        int res = 0;

        if(aNum == 1) {
            res = (a[0] - 1) / (k + 1) + 1;
        } else {
            if(a[0] - k > 0) {
                res += (a[0] - k - 1) / (k + 1) + 1;
            }
            for(int i = 1; i < aNum - 1; i++) {
                int remain = a[i] - (k * 2);
                if(remain > 0) {
                    res += (remain - 1) / (k + 1) + 1;
                }
            }
            if(aNum > 1 && a[aNum - 1] - k > 0) {
                res += (a[aNum - 1] - k - 1) / (k + 1) + 1;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}
