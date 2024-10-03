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
    int n, m;
    cin >> n >> m;
    struct Data
    {
        int idx, v;
    };
    vector<vector<Data>> d(n);
    for(int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int p, v;
            cin >> p >> v;
            p--;
            d[p].push_back({i, v});
        }
    }

    ll res = 0;
    for(auto& dd : d) {
        ll cur1 = 0, cur2 = 0; // 1: 나를 포함 X / 2: 나를 포함 O
        for(int i = 0; i < dd.size(); ++i) {
            ll nxt1, nxt2;
            nxt1 = max(cur1, cur2);
            nxt2 = cur1 + dd[i].v;
            if (i == 0 || dd[i - 1].idx + 1 != dd[i].idx) {
                nxt2 = max(nxt2, cur2 + dd[i].v);
            }

            cur1 = nxt1;
            cur2 = nxt2;
        }

        res += max(cur1, cur2);
    }

    cout << res;
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
