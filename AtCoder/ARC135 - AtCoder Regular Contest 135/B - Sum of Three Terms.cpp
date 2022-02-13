#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> s(n);
    for(auto& v : s) cin >> v;

    vector<ll> a(n + 2, 0);
    vector<ll> mx(3, INF), mn(3, 0), cur(3, 0);
    for(int i = 0; i < n - 1; ++i) {
        int idx = i % 3;
        ll v = s[i + 1] - s[i];
            cur[idx] += v;
            mn[idx] = max(mn[idx], -cur[idx]);
    }

    bool res = false;
    ll sum = mn[0] + mn[1] + mn[2];
    if(sum <= s[0]) {
        ll remain = s[0] - sum;
        if(remain <= mx[0] - mn[0]) {
            mn[0] += remain;
            remain = 0;
        }
        if(remain <= mx[1] - mn[1]) {
            mn[1] += remain;
            remain = 0;
        }
        if(remain <= mx[2] - mn[2]) {
            mn[2] += remain;
            remain = 0;
        }

        if(mn[0] <= mx[0] && mn[1] <= mx[1] && mn[2] <= mx[2]) {
            res = true;
        }
    }

    if(res == false) cout << "No\n";
    else {
        cout << "Yes\n";
        cout << mn[0] << " " << mn[1] << " " << mn[2] << " ";
        for(int i = 0; i < n - 1; ++i) {
            int idx = i % 3;
            ll v = s[i + 1] - s[i];
            mn[idx] = v + mn[idx];
            cout << mn[idx] << " ";
        }
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
