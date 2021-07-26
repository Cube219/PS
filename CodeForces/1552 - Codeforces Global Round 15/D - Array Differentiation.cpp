#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
int d[11];

bool res;
int sum1, sum2;
int cnt1, cnt2;

void bt(int cur)
{
    if(cur == n) {
        if(sum1 == sum2 && cnt1 > 0 && cnt2 > 0) {
            res = true;
        }
        return;
    }

    cnt1++;
    sum1 += d[cur];
    bt(cur + 1);
    if(res == true) return;
    cnt1--;
    sum1 -= d[cur];

    cnt2++;
    sum2 += d[cur];
    bt(cur + 1);
    if(res == true) return;
    cnt2--;
    sum2 -= d[cur];

    bt(cur + 1);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = false;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
            d[i] = abs(d[i]);
            if(d[i] == 0) res = true;
        }

        sum1 = 0;
        sum2 = 0;
        cnt1 = 0;
        cnt2 = 0;
        bt(0);

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
