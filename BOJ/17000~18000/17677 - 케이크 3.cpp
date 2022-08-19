#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <queue>
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
    Fenwick(int _n) : n(_n + 1), t(n + 1, 0) {}

    void update(int pos, ll dv)
    {
        for(pos++; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    ll query(int pos)
    {
        ll res = 0;
        for(pos++; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    struct Node { ll v, c; int idx; };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.v >> v.c;

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) { return l.c < r.c; });
    for(int i = 0; i < n; ++i) d[i].idx = i;
    vector<Node> d2 = d;
    sort(d2.begin(), d2.end(), [](const auto& l, const auto& r) { return l.v > r.v; });
    vector<int> pos(n);
    for(int i = 0; i < n; ++i) {
        pos[d2[i].idx] = i;
    }

    struct DnCOpt { int s, e, mnj, mxj; };
    vector<DnCOpt> q;
    q.push_back({ 0, n - 1, 0, n - m + 1 });

    ll res = -LNF;
    while(!q.empty()) {
        vector<DnCOpt> nxt;

        Fenwick sumsg(n), cntsg(n);
        auto update = [&](int idx, bool isAdd) {
            idx = pos[idx];
            if(isAdd) {
                sumsg.update(idx, d2[idx].v);
                cntsg.update(idx, 1);
            } else {
                sumsg.update(idx, -d2[idx].v);
                cntsg.update(idx, -1);
            }
        };
        auto query = [&]() {
            int lo = -1, hi = n;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(cntsg.query(mid) <= m - 2) lo = mid;
                else hi = mid;
            }
            if(lo == -1) return -LNF;
            else return sumsg.query(lo);
        };

        int l = 0, r = -1;
        for(auto [s, e, mnj, mxj] : q) {
            int i = (s + e) / 2;
            while(r < i) update(++r, true);
            while(l < mnj) update(l++, false);

            int mxl = min(mxj, i - m + 1);
            ll mx = -LNF;
            int pivot = mnj;
            update(r, false);
            for(int j = mnj; j <= mxl; ++j) {
                update(j, false);
                ll v = query();
                if(v > -LNF) {
                    v -= (d[i].c - d[j].c) * 2;
                    v += d[i].v + d[j].v;
                    if(mx < v) {
                        mx = v;
                        pivot = j;
                    }
                }
                if(j == mxl) update(j, true);
                else l++;
            }
            update(r, true);

            if(pivot != -1) {
                if(s <= i - 1) {
                    nxt.push_back({ s, i - 1, mnj, pivot });
                }
                if(i + 1 <= e) {
                    nxt.push_back({ i + 1, e, pivot, mxj });
                }
            }

            res = max(res, mx);
        }

        q = move(nxt);
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
