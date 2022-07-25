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
    int m, n;
    cin >> m >> n;
    struct Node
    {
        int a, b;
    };
    vector<Node> dd(n);
    for(auto& v : dd) cin >> v.a;
    for(auto& v : dd) cin >> v.b;

    sort(dd.begin(), dd.end(), [](const auto& l, const auto& r) {
        return l.b < r.b;
    });

    for(int i = 1; i < n; ++i) {
        if(dd[i - 1].b == dd[i].b) {
            cout << "-1";
            return;
        }
    }

    if(n == m) {
        for(auto [a, b] : dd) {
            if(a != b) {
                cout << "-1";
                return;
            }
        }
        cout << "0";
        return;
    }

    // b -> a
    auto p = [&](int rot) {
        ll res = 0;

        auto d = dd;
        d[0].a += m * rot;
        if(d[0].b > d[0].a) return LNF;
        res = d[0].a - d[0].b;

        int mn = d[0].a + 1;
        int mx = d[0].a + m - 1;
        for(int i = 1; i < n; ++i) {
            while(d[i].a < mn) d[i].a += m;
            if(d[i].b > d[i].a || d[i].a > mx) return LNF;

            res += d[i].a - d[i].b;
            mn = max(mn, d[i].a + 1);
        }
        return res;
    };

    ll res = LNF;
    for(int i = 0; i < 3; ++i) {
        res = min(res, p(i));
    }
    if(res == LNF) res = -1;

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
