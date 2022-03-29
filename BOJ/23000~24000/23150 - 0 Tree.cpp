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
    vector<ll> a(n);
    for(auto& v : a) cin >> v;
    vector<vector<pair<int, ll>>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    struct Res
    {
        int u, v;
        ll w;
    };
    vector<Res> res;
    bool pos = true;
    vector<ll> egCost(n);

    auto apply = [&](int src, int mid, int dst, ll w, int type) {
        res.push_back({ src, dst, w });
        a[src] ^= w;
        a[dst] ^= w;

        if(type == 0) { // src, dst
            egCost[src] += w;
            egCost[dst] -= w;
        } else if(type == 1) { // src, mid
            egCost[src] += w;
            egCost[mid] -= w;
        } else { // mid, dst
            egCost[mid] += w;
            egCost[dst] -= w;
        }
    };

    auto remove = [&](int src, int mid, int dst, bool parPath) {
        if(parPath == false) apply(src, mid, dst, a[src], 0);
        else apply(src, mid, dst, a[src], 1);

        ll w = abs(egCost[src]) / 2;
        if(abs(egCost[src]) & 1) return false;

        if(egCost[src] < 0) {
            if(parPath == false) {
                apply(src, mid, dst, w, 0);
                apply(src, mid, dst, w, 0);
            } else {
                apply(src, mid, dst, w, 1);
                apply(src, mid, dst, w, 1);
            }
        } else {
            if(parPath == false) {
                apply(dst, mid, src, w, 0);
                apply(dst, mid, src, w, 0);
            } else {
                apply(dst, mid, src, w, 2);
                apply(dst, mid, src, w, 2);
            }
        }
        return true;
    };

    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        int last = -1;
        for(auto [nxt, cost] : g[cur]) {
            if(nxt == pre) continue;

            egCost[nxt] = cost;
            self(self, nxt, cur);
            if(pos == false) return;

            if(last != -1) {
                // Remove last node
                if(remove(last, cur, nxt, false) == false) {
                    pos = false;
                    return;
                }
            }
            last = nxt;
        }

        if(last != -1) {
            if(pre != -1) {
                if(remove(last, cur, pre, true) == false) pos = false;
                return;
            }

            res.push_back({ last, cur, a[last] });
            egCost[last] += a[last];
            a[cur] ^= a[last];
            ll w = abs(egCost[last]) / 2;
            if(a[cur] != 0 || egCost[last] > 0 || (abs(egCost[last]) & 1)) pos = false;
            else {
                res.push_back({ last, cur, w });
                res.push_back({ last, cur, w });
            }
        }
    };
    dfs(dfs, 0, -1);

    if(n == 1 && a[0] != 0) pos = false;

    if(pos == false) cout << "NO\n";
    else {
        cout << "YES\n";
        cout << res.size() << "\n";
        for(auto [u, v, w] : res) cout << u + 1 << " " << v + 1 << " " << w << "\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
