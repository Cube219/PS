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
    int n;
    cin >> n;
    vector<int> w(n);
    for(auto& v : w) cin >> v;
    vector<vector<int>> g(n, vector<int>(n));
    for(auto& v : g) for(auto& v2 : v) cin >> v2;

    struct QNode
    {
        int v, cost;
        bool operator<(const QNode& rhs) const { return cost > rhs.cost; }
    };
    priority_queue<QNode> pq;
    for(int i = 0; i < n; ++i) pq.push({ i, w[i] });
    vector<char> finish(n, false);
    int res = 0;
    while(!pq.empty()) {
        auto [cur, cost] = pq.top(); pq.pop();
        if(finish[cur]) continue;

        res += cost;
        finish[cur] = true;
        for(int i = 0; i < n; ++i) {
            if(finish[i]) continue;
            pq.push({ i, g[cur][i] });
        }
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
