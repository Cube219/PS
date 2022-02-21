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
    int n, k;
    cin >> n >> k;
    vector<vector<int>> d;
    ll base = 0;
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        vector<int> tmp(num);
        for(auto& v : tmp) cin >> v;
        sort(tmp.begin(), tmp.end());

        base += tmp[0];
        if(num > 1) {
            d.emplace_back();
            for(int j = 1; j < num; ++j) {
                d.back().push_back(tmp[j] - tmp[0]);
            }
        }
    }
    n = d.size();

    sort(d.begin(), d.end());

    struct Node
    {
        int i, j;
        ll v;
        bool operator<(const Node& rhs) const { return v > rhs.v; }
    };
    ll res = base;
    priority_queue<Node> pq;
    pq.push({ 0, 0, d[0][0] });
    for(int kk = 0; kk < k - 1; ++kk) {
        auto [i, j, v] = pq.top(); pq.pop();

        res += v + base;
        // j 증가 (d[i][j] -> d[i][j + 1])
        if(j < (int)d[i].size() - 1) {
            pq.push({ i, j + 1, v - d[i][j] + d[i][j + 1] });
        }
        // i 증가
        if(i < n - 1) {
            // d[i + 1][0]을 새로 추가
            pq.push({ i + 1, 0, v + d[i + 1][0] });
            if(j == 0) {
                // d[i][0]을 지우고 d[i + 1][0]을 새로 추가
                pq.push({ i + 1, 0, v - d[i][0] + d[i + 1][0] });
            }
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
