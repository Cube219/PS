#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
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
    ll k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
    }

    vector<int> a2 = a;
    sort(a2.begin(), a2.end());

    if(k == 1) {
        cout << a2[0];
        return;
    }

    auto ck = [&](int mx) -> bool {
        bool hasCycle = false;

        // Cycle check
        int cnt = 0;
        vector<int> comp(n, -1);
        vector<char> visit(n, false);
        for(int i = 0; i < n; ++i) {
            if(a[i] > mx) continue;
            if(comp[i] != -1) continue;

            auto dfs = [&](auto&& self, int cur) -> void {
                comp[cur] = cnt;
                visit[cur] = true;

                for(int nxt : g[cur]) {
                    if(a[nxt] > mx) continue;

                    if(visit[nxt]) {
                        hasCycle = true;
                        break;
                    }

                    if(comp[nxt] != -1) continue;

                    self(self, nxt);
                }

                visit[cur] = false;
            };
            dfs(dfs, i);

            cnt++;
        }

        if(hasCycle) return true;

        vector<int> in(n, 0), out(n, 0);
        for(int i = 0; i < n; ++i) {
            if(a[i] > mx) continue;
            for(int nxt : g[i]) {
                if(a[nxt] > mx) continue;

                in[nxt]++;
                out[i]++;
            }
        }

        queue<int> q;
        for(int i = 0; i < n; ++i) {
            if(a[i] > mx) continue;
            if(in[i] == 0) q.push(i);
        }

        vector<int> dst(n, 1);
        while(q.empty() == false) {
            int cur = q.front();
            q.pop();

            for(int nxt : g[cur]) {
                if(a[nxt] > mx) continue;

                dst[nxt] = max(dst[nxt], dst[cur] + 1);
                in[nxt]--;
                if(in[nxt] == 0) {
                    q.push(nxt);
                }
            }
        }

        int mxLen = 0;
        for(int i = 0; i < n; ++i) {
            if(a[i] > mx) continue;
            mxLen = max(mxLen, dst[i]);
        }
        if(mxLen < k) return false;
        return true;
    };

    int lo = -1, hi = n;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;

        if(ck(a2[mid])) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if(hi == n) cout << "-1";
    else cout << a2[hi];
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
