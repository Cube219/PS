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
    vector<int> t;
    Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

    void update(int pos, int dv)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    int query(int pos)
    {
        pos++;
        int res = 0;
        for(; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    struct Node
    {
        int t, x, y;
        bool isRec;
        int qIdx, cnt;

        bool operator<(const Node& rhs) const
        {
            if(t == rhs.t) {
                if(x == rhs.x) return y < rhs.y;
                return x < rhs.x;
            }
            return t < rhs.t;
        }
    };

    int n;
    vector<Node> d;
    vector<int> query;
    while(1) {
        int type;
        cin >> type;
        if(type == 0) {
            cin >> n;
        } else if(type == 1) {
            int x, y, a;
            cin >> x >> y >> a;
            d.push_back({ (int)d.size() - 1, x, y, false, -1, a });
        } else if(type == 2) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            query.push_back(0);
            int qIdx = query.size() - 1;

            d.push_back({ (int)d.size() - 1, x2, y2, true, qIdx, 1 });
            if(x1 > 1) {
                d.push_back({ (int)d.size() - 1, x1 - 1, y2, true, qIdx, -1 });
            }
            if(y1 > 1) {
                d.push_back({ (int)d.size() - 1, x2, y1 - 1, true, qIdx, -1 });
            }
            if(x1 > 1 && y1 > 1) {
                d.push_back({ (int)d.size() - 1, x1 - 1, y1 - 1, true, qIdx, 1 });
            }
        } else break;
    }

    sort(d.begin(), d.end());
    vector<Node> tmp(d.size());
    Fenwick fw(2000001);

    auto cdq = [&](auto&& self, int l, int r) -> void {
        if(l == r) return;
        int m = (l + r) / 2;
        self(self, l, m);
        self(self, m + 1, r);

        int lIdx = l, rIdx = m + 1;
        int cur = l;
        auto left = [&]() {
            if(d[lIdx].isRec == false) {
                fw.update(d[lIdx].y, d[lIdx].cnt);
            }
            tmp[cur++] = d[lIdx++];
        };
        auto right = [&]() {
            if(d[rIdx].isRec == true) {
                int qIdx = d[rIdx].qIdx;
                int w = d[rIdx].cnt;

                query[qIdx] += fw.query(d[rIdx].y) * w;
            }
            tmp[cur++] = d[rIdx++];
        };
        while(lIdx <= m && rIdx <= r) {
            if(d[lIdx].x <= d[rIdx].x) left();
            else right();
        }
        while(lIdx <= m) left();
        while(rIdx <= r) right();

        for(int i = l; i <= m; ++i) {
            if(d[i].isRec == false) {
                fw.update(d[i].y, -d[i].cnt);
            }
        }

        for(int i = l; i <= r; ++i) {
            d[i] = tmp[i];
        }
    };
    cdq(cdq, 0, d.size() - 1);

    for(ll v : query) cout << v << "\n";
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
