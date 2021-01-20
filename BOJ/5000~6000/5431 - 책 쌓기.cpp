#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
#include <utility>

using lli = long long int;

int tNum, n, d[51];
lli res, d3[51];
std::vector<int> d2;
lli tmp[51];
int tmpNum;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &d[i]);
        }

        d2.clear();
        res = 0;
        
        d2.push_back(d[0]);
        for(int i = 1; i < n; i++) {
            if(d2[i - 1] <= d[i]) {
                d2.push_back(d[i]);
                continue;
            }

            auto it = d2.begin();
            for(; it != d2.end(); it++) {
                if(*it >= d[i]) break;
            }

            int before = d2[0];
            tmpNum = 0;
            tmp[0] = 0;
            for(auto iter = d2.begin(); iter != it; iter++) {
                if(before != *iter) {
                    tmp[++tmpNum] = 1;
                } else {
                    tmp[tmpNum]++;
                }
                before = *iter;
            }
            lli v = 1;
            for(int i = 0; i <= tmpNum; i++) {
                v *= (tmp[i] + 1);
            }
            res += v;

            d2.insert(it, d[i]);
        }

        printf("%lld\n", res);
    }
                                               
    return 0;
}
