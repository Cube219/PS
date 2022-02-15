#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <set>
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
    int n, q;
    cin >> n >> q;

    Fenwick fw(n + 1);
    auto fwUpdate = [&](int l, int r, ll v) {
        fw.update(r + 1, -v);
        fw.update(l, v);
    };
    auto fwQuery = [&](int pos) {
        return fw.query(pos);
    };
    vector<ll> col(n + 1, 0);
    struct Line
    {
        int l, r, c;
        bool operator<(const Line& rhs) const
        {
            return l < rhs.l;
        }
    };
    set<Line> lines;
    lines.insert({ 0, n - 1, 1 });
    for(int qq = 0; qq < q; ++qq) {
        string str;
        cin >> str;
        if(str[0] == 'C') {
            int l, r, c;
            cin >> l >> r >> c;
            l--; r--;

            // remove lines
            auto it = lines.upper_bound({ l, l, 0 });
            if(it != lines.begin()) it = prev(it);
            while(it != lines.end()) {
                if(it->r < l) {
                    it = next(it);
                    continue;
                }
                if(it->l > r) break;

                Line leftLine = { it->l, l - 1, it->c };
                Line cenLine = { max(it->l, l), min(it->r, r), it->c };
                Line rightLine = { r + 1, it->r, it->c };

                auto nxtIt = next(it);
                lines.erase(it);
                it = nxtIt;

                if(leftLine.l <= leftLine.r) lines.insert(leftLine);
                if(rightLine.l <= rightLine.r) lines.insert(rightLine);
                fwUpdate(cenLine.l, cenLine.r, col[cenLine.c]);
            }
            // add line
            fwUpdate(l, r, -col[c]);
            lines.insert({ l, r, c });
        } else if(str[0] == 'A') {
            int c, x;
            cin >> c >> x;
            col[c] += x;
        } else { // 'Q'
            int pos;
            cin >> pos;
            pos--;

            ll res = fwQuery(pos);

            auto it = lines.upper_bound({ pos, pos, 0 });
            if(it != lines.begin()) {
                it = prev(it);
                if(it->l <= pos && pos <= it->r) {
                    res += col[it->c];
                }
            }
            cout << res << "\n";
        }
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
