#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#ifndef CUBE_PS
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
#include <cmath>
#include <memory.h>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

ll map[201][201];

void solve()
{
    int n;
    cin >> n;
    struct Node
    {
        int x, y, p;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.x >> v.y >> v.p;

    auto ck = [&](ll s) -> bool {

        memset(map, 0, sizeof(map));

        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                ll dx = abs(d[i].x - d[j].x);
                ll dy = abs(d[i].y - d[j].y);

                // i -> j
                ll power = s * d[i].p;
                if(power >= dx + dy) map[i][j] = 1;

                // j -> i
                power = s * d[j].p;
                if(power >= dx + dy) map[j][i] = 1;
            }
        }

        for(int i = 0; i < n; ++i) {
            vector<char> reach(n, false);
            reach[i] = true;
            queue<int> q;
            q.push(i);

            while(q.empty() == false) {
                int cur = q.front(); q.pop();

                for(int j = 0; j < n; ++j) {
                    if(reach[j]) continue;
                    if(map[cur][j] == 0) continue;

                    reach[j] = true;
                    q.push(j);
                }
            }

            bool ck = true;
            for(int j = 0; j < n; ++j) {
                if(reach[j] == false) ck = false;
            }
            if(ck) return true;
        }
        return false;
    };

    ll lo = 0, hi = 4'000'000'000;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(ck(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi;
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
