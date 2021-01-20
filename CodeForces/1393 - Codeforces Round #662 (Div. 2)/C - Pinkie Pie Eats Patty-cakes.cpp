#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
int n, d[100001];
int maxNum;
vector<int> maxs;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        maxs.clear();
        maxNum = 0;

        scanf("%d", &n);

        for(int i = 1; i <= n; i++) {
            d[i] = 0;
        }

        for(int i = 0; i < n; i++) {
            int a;
            scanf("%d", &a);

            d[a]++;
            if(d[a] == maxNum) maxs.push_back(a);
            else if(d[a] > maxNum) {
                maxNum = d[a];
                maxs.clear();
                maxs.push_back(a);
            }
        }

        int res, mod;

        if(maxNum == 2) {
            res = n - 1 - maxs.size();
        } else {
            int t = maxs.size() - 1;

            res = (n - maxNum - t) / (maxNum - 1);
            mod = (n - maxNum - t) % (maxNum - 1);
            // if(maxs.size() - 1 > mod) res--;
        }

        printf("%d\n", res);
    }

    return 0;
}