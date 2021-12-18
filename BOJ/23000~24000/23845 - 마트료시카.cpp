#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
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
    vector<ll> d(n);
    for(auto& v : d)cin >> v;

    sort(d.begin(), d.end());

    vector<multiset<int>> cnt(100001);
    ll res = 0;
    for(ll v : d) {
        if(cnt[v - 1].size() > 0) {
            auto it = prev(cnt[v - 1].end());
            cnt[v].insert(*it + 1);
            cnt[v - 1].erase(it);
        } else {
            cnt[v].insert(1);
        }
    }

    for(int i = 1; i <= 100000; ++i) {
        for(int c : cnt[i]) {
            res += (ll)c * i;
        }
    }

    cout << res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
