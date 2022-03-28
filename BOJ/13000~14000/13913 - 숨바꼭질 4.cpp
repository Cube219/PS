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
    int n, k;
    cin >> n >> k;
    vector<int> d(100001, INF);
    vector<int> rec(100001, -1);

    struct Node
    {
        int x, t;
    };
    queue<Node> q;
    q.push({ n, 0 });
    d[n] = 0;
    while(q.empty() == false) {
        auto [x, t] = q.front();
        q.pop();
        if(d[x] != t) continue;

        // left
        if(x > 0 && d[x - 1] > t + 1) {
            d[x - 1] = t + 1;
            rec[x - 1] = x;
            q.push({ x - 1, t + 1 });
        }

        // right
        if(x < 100000 && d[x + 1] > t + 1) {
            d[x + 1] = t + 1;
            rec[x + 1] = x;
            q.push({ x + 1, t + 1 });
        }

        // *x
        if(x * 2 <= 100000 && d[x * 2] > t + 1) {
            d[x * 2] = t + 1;
            rec[x * 2] = x;
            q.push({ x * 2, t + 1 });
        }
    }

    vector<int> res;
    int cur = k;
    while(cur != n) {
        res.push_back(cur);
        cur = rec[cur];
    }
    res.push_back(n);

    cout << d[k] << "\n";
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i] << " ";
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
