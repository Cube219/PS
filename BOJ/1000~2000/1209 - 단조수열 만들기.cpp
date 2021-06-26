#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 100000000000000;

int n, m, a[2001];
vector<int> v;
ll dp[2001][2001];

ll process()
{
    for(int i = 0; i < m; ++i) {
        dp[0][i] = abs(a[0] - v[i]);
    }
    for(int i = 1; i < n; ++i) {
        ll minV = INF;
        for(int j = 0; j < m; ++j) {
            minV = min(minV, dp[i - 1][j]);
            dp[i][j] = abs(a[i] - v[j]) + minV;
        }
    }

    ll res = INF;
    for(int i = 0; i < m; ++i) {
        res = min(res, dp[n - 1][i]);
    }
    return res;
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
        v.push_back(a[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    m = v.size();

    ll res = process();
    reverse(v.begin(), v.end());
    res = min(res, process());
    
    cout << res;

    return 0;
}
