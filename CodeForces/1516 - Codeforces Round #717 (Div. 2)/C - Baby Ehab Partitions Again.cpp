#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int d[101];
bool dp[200001];
int idx[200001], idx2[200001], lea[200001];
int sum;

void solve()
{
    int s2 = sum / 2;
    int t = -1;
    sort(d, d + n);

    dp[0] = true;
    for(int i = 0; i < n; ++i) {
        for(int j = s2; j >= d[i]; --j) {
            if(dp[j - d[i]] == true) {
                dp[j] = true;
                idx[j] = d[i];
                idx2[j] = i;
            }
        }
    }
    if(dp[s2] == false) {
        cout << "0";
        return;
    }

    int mincnt = 9876542, minv = 0;
    for(int i = 0; i < n; ++i) {
        int dd = d[i];
        int curcnt = 0;
        while(dd % 2 == 0) {
            curcnt++;
            dd /= 2;
        }
        if(mincnt > curcnt) {
            mincnt = curcnt;
            minv = d[i];
        }
    }

    cout << "1\n";
    cout << lea[minv];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        sum += d[i];
        if(lea[d[i]] == 0) {
            lea[d[i]] = i + 1;
        }
    }
    if(sum % 2 == 1) {
        cout << "0";
    } else {
        solve();
    }

    return 0;
}
