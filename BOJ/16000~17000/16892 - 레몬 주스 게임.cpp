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
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    vector<int> res(n + 1, 0);
    for(int v : a) res[1] = max(res[1], v);

    auto odd = [&]() {
        if(n == 1) return;

        int n2 = n / 2;
        vector<int> d(n, -1);
        for(int i = 1; i < n - 1; ++i) {
            int len = abs(i - n2);
            int v = max(min(a[i - 1], a[i]), min(a[i], a[i + 1]));
            d[len] = max(d[len], v);
        }

        int sz = n, cur = 0;
        int idx = 0;
        while(sz > 1) {
            cur = max(cur, d[idx]);
            res[sz] = max(res[sz], cur);

            sz -= 2;
            idx++;
        }
    };
    auto even = [&]() {
        int n2 = n / 2;
        vector<int> d(n, -1);
        for(int i = 1; i < n; ++i) {
            int len = abs(i - n2);
            int v = max(a[i - 1], a[i]);
            d[len] = max(d[len], v);
        }

        int sz = n, cur = 0;
        int idx = 0;
        while(sz > 0) {
            cur = max(cur, d[idx]);
            res[sz] = max(res[sz], cur);

            sz -= 2;
            idx++;
        }
    };

    if(n % 2 == 0) {
        even();
        auto a2 = a;
        n--;
        a.pop_back();
        odd();
        a.assign(a2.begin() + 1, a2.end());
        odd();
    } else {
        odd();
        if(n > 1) {
            auto a2 = a;
            n--;
            a.pop_back();
            even();
            a.assign(a2.begin() + 1, a2.end());
            even();
        } else {
            n--;
        }
    }

    for(int i = n + 1; i >= 1; --i) {
        cout << res[i] << " ";
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
