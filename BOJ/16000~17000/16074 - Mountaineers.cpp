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

struct DSU
{
    int n;
    vector<int> par, sz;

    DSU(int _n) : n(_n), par(_n)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while(x != par[x]) x = par[x] = par[par[x]];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        par[b] = a;
        return true;
    }
};

void solve()
{
    int n, m, qNum;
    cin >> n >> m >> qNum;
    vector<vector<int>> map(n, vector<int>(m));
    for(auto& v : map) for(auto& v2 : v) cin >> v2;
    struct Query
    {
        int sx, sy, ex, ey;
        int idx, lo, hi;
    };
    vector<Query> qList(qNum);
    for(int i = 0; i < qNum; ++i) {
        auto& q = qList[i];
        cin >> q.sx >> q.sy >> q.ex >> q.ey;
        q.sx--; q.sy--; q.ex--; q.ey--;
        q.idx = i;
        q.lo = 0;
        q.hi = 1000000;
    }

    struct Block
    {
        int x, y, h;
    };
    vector<Block> h;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            h.push_back({ i, j, map[i][j] });
        }
    }
    sort(h.begin(), h.end(), [](const auto& l, const auto& r) {
        return l.h < r.h;
    });

    vector<int> res(qNum), dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };
    while(qList.size() > 0) {
        sort(qList.begin(), qList.end(), [](const auto& l, const auto& r) {
            return (l.lo + l.hi) / 2 < (r.lo + r.hi) / 2;
        });

        int i = 0;
        DSU dsu(n * m);
        vector<Query> nQList;
        for(auto& q : qList) {
            if(q.lo + 1 == q.hi) {
                res[q.idx] = q.hi;
                continue;
            }
            if(pair(q.sx, q.sy) == pair(q.ex, q.ey)) {
                res[q.idx] = map[q.sx][q.sy];
                continue;
            }
            int mid = (q.lo + q.hi) / 2;

            for(; i < h.size() && h[i].h <= mid; ++i) {
                for(int j = 0; j < 4; ++j) {
                    int nx = h[i].x + dx[j];
                    int ny = h[i].y + dy[j];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                    if(map[nx][ny] <= h[i].h) dsu.uni(nx * m + ny, h[i].x * m + h[i].y);
                }
            }

            if(dsu.find(q.sx * m + q.sy) == dsu.find(q.ex * m + q.ey)) {
                q.hi = mid;
            } else {
                q.lo = mid;
            }
            nQList.push_back(q);
        }

        qList = move(nQList);
    }

    for(int v : res) cout << v << "\n";
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
