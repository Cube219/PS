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

struct Fenwick
{
    int n;
    vector<ll> t;
    Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

    void update(int pos, ll dv)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    ll query(int pos)
    {
        pos++;
        ll res = 0;
        for(; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> pos(n);
    for(int i = 0; i < m; ++i) {
        int v;
        cin >> v;
        v--;
        pos[v].push_back(i);
    }
    vector<int> req(n);
    for(auto& v : req) cin >> v;
    struct Query
    {
        int l, r, a;
    };
    int qNum;
    cin >> qNum;
    vector<Query> qList(qNum);
    for(auto& q : qList) {
        cin >> q.l >> q.r >> q.a;
        q.l--; q.r--;
    }

    vector<int> lo(n, -1), hi(n, qNum);
    while(1) {
        vector<vector<int>> midList(qNum + 1);
        int mxMid = -1;
        for(int i = 0; i < n; ++i) {
            if(lo[i] + 1 == hi[i]) continue;
            int mid = (lo[i] + hi[i]) / 2;
            midList[mid].push_back(i);
            mxMid = max(mxMid, mid);
        }
        if(mxMid == -1) break;

        Fenwick fw(m + 1);
        auto fwUpdate = [&](int l, int r, int v) {
            fw.update(l, v);
            fw.update(r + 1, -v);
        };
        auto fwQuery = [&](int pos) {
            return fw.query(pos);
        };
        for(int i = 0; i <= mxMid; ++i) {
            auto& q = qList[i];
            if(q.l <= q.r) {
                fwUpdate(q.l, q.r, q.a);
            }
            else {
                fwUpdate(0, q.r, q.a);
                fwUpdate(q.l, m - 1, q.a);
            }

            for(int cur : midList[i]) {
                ll v = 0;
                for(int p : pos[cur]) {
                    v += fwQuery(p);
                    if(v >= req[cur]) break;
                }
                if(v >= req[cur]) {
                    hi[cur] = i;
                } else {
                    lo[cur] = i;
                }
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        if(hi[i] == qNum) cout << "NIE\n";
        else cout << hi[i] + 1 << "\n";
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
