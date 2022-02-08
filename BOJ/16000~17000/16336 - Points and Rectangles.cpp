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
    struct Node
    {
        int qIdx, x, y;
        bool isRec, isNeg;
    };

    int q;
    cin >> q;
    vector<Node> d;
    vector<ll> res(q, 0);
    vector<int> yy;
    for(int i = 0; i < q; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int x, y;
            cin >> x >> y;
            d.push_back({ i, x, y, false, false });

            yy.push_back(y);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            d.push_back({ i, x2, y2, true, false });
            d.push_back({ i, x1 - 1, y2, true, true });
            d.push_back({ i, x2, y1 - 1, true, true });
            d.push_back({ i, x1 - 1, y1 - 1, true, false });

            yy.push_back(y2);
            yy.push_back(y1 - 1);
        }
    }
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    for(auto& v : d) {
        v.y = lower_bound(yy.begin(), yy.end(), v.y) - yy.begin();
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        return l.qIdx < r.qIdx;
    });
    auto d2 = d;

    Fenwick fw(yy.size());
    vector<Node> tmp(d.size());
    auto cdq = [&](auto&& self, int l, int r) -> void {
        if(l == r) return;
        int m = (l + r) / 2;
        self(self, l, m);
        self(self, m + 1, r);

        int cl = l, cr = m + 1, cur = l;
        auto left = [&]() {
            if(d[cl].isRec == false) {
                fw.update(d[cl].y, 1);
            }
            tmp[cur++] = d[cl++];
        };
        auto right = [&]() {
            if(d[cr].isRec == true) {
                int w = d[cr].isNeg ? -1 : 1;
                res[d[cr].qIdx] += fw.query(d[cr].y) * w;
            }
            tmp[cur++] = d[cr++];
        };
        while(cl <= m && cr <= r) {
            if(d[cl].x <= d[cr].x) left();
            else right();
        }
        while(cl <= m) left();
        while(cr <= r) right();
        for(int i = l; i <= m; ++i) {
            if(d[i].isRec == false) fw.update(d[i].y, -1);
        }
        for(int i = l; i <= r; ++i) {
            d[i] = tmp[i];
        }

        cl = l; cr = m + 1; cur = l;
        auto left2 = [&]() {
            if(d2[cl].isRec == true) {
                int w = d2[cl].isNeg ? -1 : 1;
                fw.update(d2[cl].y, w);
            }
            tmp[cur++] = d2[cl++];
        };
        auto right2 = [&]() {
            if(d2[cr].isRec == false) {
                res[d2[cr].qIdx] += fw.query(yy.size() - 1);
                if(d2[cr].y > 0) res[d2[cr].qIdx] -= fw.query(d2[cr].y - 1);
            }
            tmp[cur++] = d2[cr++];
        };
        while(cl <= m && cr <= r) {
            if(d2[cl].x >= d2[cr].x) left2();
            else right2();
        }
        while(cl <= m) left2();
        while(cr <= r) right2();
        for(int i = l; i <= m; ++i) {
            if(d2[i].isRec == true) {
                int w = d2[i].isNeg ? -1 : 1;
                fw.update(d2[i].y, -w);
            }
        }
        for(int i = l; i <= r; ++i) {
            d2[i] = tmp[i];
        }
    };
    cdq(cdq, 0, d.size() - 1);

    ll cur = 0;
    for(ll v : res) {
        cur += v;
        cout << cur << "\n";
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
