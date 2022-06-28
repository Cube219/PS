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
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    if(n <= 4) {
        set<ll> mp;
        for(int i = 0; i < n; ++i) {
            mp.insert(d[i]);
        }
        bool ck = true;
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                for(int k = j + 1; k < n; ++k) {
                    ll v = (ll)d[i] + (ll)d[j] + (ll)d[k];

                    if(mp.find(v) == mp.end()) {
                        ck = false;
                        goto end;
                    }
                }
            }
        }
        end:
        if(ck) {
            cout << "YES\n";
            return;
        }
    }

    sort(d.begin(), d.end());
    int mx = d[n - 1];
    if(d[n - 2] != 0 || d[1] != 0) {
        cout << "NO\n";
        return;
    }

    if(d[0] == 0 || d[n - 1] == 0) {
        cout << "YES\n";
        return;
    }

    if(d[0] != -mx) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
