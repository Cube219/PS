#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for(auto& v : a) cin >> v;

    multiset<ll> c1, c2;
    for(int i = 1; i < n; ++i) {
        c1.insert(a[i] - a[i - 1]);
        if(a[i] % a[i - 1] == 0) c2.insert(a[i] / a[i - 1]);
    }

    for(int i = 0; i < m; ++i) {
        ll pos, v;
        cin >> pos >> v;
        pos--;

        // pos - 1, pos
        if(pos > 0) {
            auto it = c1.find(a[pos] - a[pos - 1]);
            c1.erase(it);
            if(a[pos] % a[pos - 1] == 0) {
                auto it = c2.find(a[pos] / a[pos - 1]);
                c2.erase(it);
            }

            c1.insert(v - a[pos - 1]);
            if(v % a[pos - 1] == 0) c2.insert(v / a[pos - 1]);
        }

        // pos, pos + 1
        if(pos < n - 1) {
            auto it = c1.find(a[pos + 1] - a[pos]);
            c1.erase(it);
            if(a[pos + 1] % a[pos] == 0) {
                auto it = c2.find(a[pos + 1] / a[pos]);
                c2.erase(it);
            }

            c1.insert(a[pos + 1] - v);
            if(a[pos + 1] % v == 0) c2.insert(a[pos + 1] / v);
        }

        a[pos] = v;

        ll mn = *c1.begin();
        ll mx = *c1.rbegin();
        if(mn == mx && mn > 0) {
            cout << "+\n";
            continue;
        }

        if(c2.size() == n - 1) {
            mn = *c2.begin();
            mx = *c2.rbegin();
            if(mn == mx && mn > 0) {
                cout << "*\n";
                continue;
            }
        }
        cout << "?\n";
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
