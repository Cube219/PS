#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <algorithm>
using namespace std;

int tNum;
int n, k, d[200001], dNum;

using lli = long long int;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &k);
        dNum = 0;
        for(int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);
            if(a % k != 0) {
                d[dNum++] = a % k;
            }
        }

        sort(d, d + dNum);

        int maxCount = 0, maxVal;
        int curCount = 1, curVal = d[0];
        for(int i = 1; i < dNum; i++) {
            if(d[i] == curVal) {
                curCount++;
            } else {
                if(maxCount < curCount) {
                    maxCount = curCount;
                    maxVal = curVal;
                }

                curCount = 1;
                curVal = d[i];
            }
        }
        if(maxCount < curCount) {
            maxCount = curCount;
            maxVal = curVal;
        }

        lli res;
        if(dNum == 0) {
            res = 0;
        } else {
            res = (lli)(maxCount - 1) * (lli)k + (lli)(k-maxVal) + (lli)1;
        }

        printf("%lld\n", res);
    }

    return 0;
}
