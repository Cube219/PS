#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n;
char d[501];
int dLen;
vector<int> a;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%s", d);
        dLen = strlen(d);
        
        int cnt = 0;
        for(int i = 0; i < dLen; i++) {
            if(d[i] == '0') {
                if(cnt > 0) {
                    a.push_back(cnt);
                }
                cnt = 0;
            } else {
                cnt++;
            }
        }
        if(cnt > 0) a.push_back(cnt);
        sort(a.begin(), a.end());

        int res = 0;
        while(a.empty() == false) {
            res += a.back();
            a.pop_back();

            if(a.empty() == true) break;
            a.pop_back();
        }
        printf("%d\n", res);
    }

    return 0;
}
