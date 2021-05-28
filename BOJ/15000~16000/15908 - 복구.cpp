#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n;
int a[100001], b[100001];
int dp[100001];
bool pos[100001];

bool ck(int k)
{
    int knum = 0;
    for(int i = n - 1; i >= 0; --i) {
        int num = a[i];
        dp[i] = INF;
        pos[i] = false;
        if(i + num <= n) {
            if(knum + dp[i + num] <= num - 1) {
                dp[i] = -knum;
                if(b[i] > k) dp[i]--;
                pos[i] = true;
            }
        }

        dp[i] = min(dp[i], dp[i + 1]);
        if(b[i] > k) knum++;
    }
    for(int i = 0; i < n - 1; ++i) {
        if(pos[i] == true) return true;

        if(b[i] <= k) continue;
        if(pos[i] == false) return false;
    }
    return true;
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
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    int l = -1, r = 100000;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(ck(m) == true) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;

    return 0;
}
