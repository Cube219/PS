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
    struct Node {
        int p, d;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.p >> v.d;

    if(n == 0) {
        cout << "0";
        return;
    }

    sort(d.begin(), d.end(), [](auto& l, auto& r) {
        return l.d > r.d;
    });

    priority_queue<int> pq;
    ll res = 0;
    int curday = d[0].d;
    for(auto [cost, day] : d) {
        while(curday > day) {
            if(!pq.empty()) {
                res += pq.top();
                pq.pop();
            }
            curday--;
        }
        pq.push(cost);
    }

    while(curday > 0) {
        if(!pq.empty()) {
            res += pq.top();
            pq.pop();
        }
        curday--;
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
