#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<ll>> d(n, vector<ll>(m));
    for(auto& v1 : d)
        for(auto& v2 : v1) cin >> v2;
    int qNum;
    cin >> qNum;
    struct Query
    {
        int sx, sy, ex, ey;
    };
    vector<Query> q(qNum);
    for(auto& v : q) {
        cin >> v.sx >> v.sy >> v.ex >> v.ey;
        v.sx--;
        v.sy--; v.ex--;
        v.ey--;

        if(v.sy > v.ey) {
            swap(v.sx, v.ex);
            swap(v.sy, v.ey);
        }
    }

    vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };
    vector<vector<ll>> dst(n, vector<ll>(m));
    auto dijk = [&](int l, int r, int stx, int mid) -> void {
        for(int i = 0; i < n; ++i) {
            for(int j = l; j <= r; ++j) {
                dst[i][j] = LNF;
            }
        }
        struct PNode
        {
            int x, y;
            ll cost;
            bool operator<(const PNode& rhs) const
            {
                return cost > rhs.cost;
            }
        };
        priority_queue<PNode> pq;
        pq.push({ stx, mid, d[stx][mid] });
        dst[stx][mid] = d[stx][mid];
        while(pq.empty() == false) {
            auto [x, y, cost] = pq.top();
            pq.pop();
            if(cost != dst[x][y]) continue;

            for(int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(ny < l || r < ny) continue;
                if(dst[nx][ny] > cost + d[nx][ny]) {
                    dst[nx][ny] = cost + d[nx][ny];
                    pq.push({ nx, ny, dst[nx][ny] });
                }
            }
        }
    };
    vector<ll> res(qNum, LNF);

    auto dnc = [&](auto&& self, int l, int r, const vector<int>& qIdx) -> void {
        if(l > r) return;

        int mid = (l + r) / 2;
        for(int i = 0; i < n; ++i) {
            dijk(l, r, i, mid);
            for(int qi : qIdx) {
                auto [sx, sy, ex, ey] = q[qi];
                res[qi] = min(res[qi], dst[sx][sy] + dst[ex][ey] - d[i][mid]);
            }
        }

        vector<int> ql, qr;
        for(int qi : qIdx) {
            auto [sx, sy, ex, ey] = q[qi];
            if(ey < mid) ql.push_back(qi);
            else if(mid < sy) qr.push_back(qi);
        }

        self(self, l, mid - 1, ql);
        self(self, mid + 1, r, qr);
    };
    vector<int> qi(qNum);
    iota(qi.begin(), qi.end(), 0);
    dnc(dnc, 0, m - 1, qi);

    for(ll v : res) cout << v << "\n";
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
