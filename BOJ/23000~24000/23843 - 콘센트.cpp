#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
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
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    sort(d.begin(), d.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(int i = 0; i < m; ++i) {
        pq.push(0);
    }

    for(int i = d.size() - 1; i >= 0; --i) {
        ll cur = pq.top();
        pq.pop();
        pq.push(cur + d[i]);
    }
    ll res = 0;
    while(!pq.empty()) {
        res = max(res, pq.top());
        pq.pop();
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
