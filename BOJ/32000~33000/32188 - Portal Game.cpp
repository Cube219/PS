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
    int n, c;
    cin >> n >> c;
    struct Portal
    {
        int t = -1;
        int dst;
    };
    vector<Portal> d(n);
    for(int i = 0; i < c; ++i) {
        int t, a, b;
        cin >> t >> a >> b;
        d[a] = {t, b};
    }

    vector<int> dis(n, INF);
    struct PQ
    {
        int cur, cost;
        bool operator<(const PQ& rhs) const {
            return cost > rhs.cost;
        }
    };
    priority_queue<PQ> q;
    q.push({0, 0});
    dis[0] = 0;
    while(!q.empty()) {
        auto [cur, cost] = q.top();
        q.pop();
        if (cur == n - 1) break;

        if (d[cur].t == -1 || d[cur].t == 1) {
            if (dis[cur + 1] > cost + 1) {
                dis[cur + 1] = cost + 1;
                q.push({cur + 1, cost + 1});
            }
        }
        if (d[cur].t == 0 || d[cur].t == 1) {
            if (dis[d[cur].dst] > cost) {
                dis[d[cur].dst] = cost;
                q.push({d[cur].dst, cost});
            }
        }
    }

    if (dis[n - 1] == INF) cout << "-1";
    else cout << dis[n - 1];
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
