#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;

    vector<int> d(20001, INF);
    vector<pair<int, int>> pre(20001, { -1, -1 });

    queue<pair<int, int>> q;
    for(int i = 1; i < 10; ++i) {
        int digit = n * i % 10;
        if(digit != 0 && digit != 1) continue;

        q.push({ n * i / 10, digit });
        d[n * i / 10] = 0;
        pre[n * i / 10] = { -1, digit };
    }

    while(q.empty() == false) {
        auto [cur, cost] = q.front();
        q.pop();

        for(int i = 0; i < 10; ++i) {
            int nxt = cur + n * i;
            int digit = nxt % 10;
            if(digit != 0 && digit != 1) continue;

            if(d[nxt / 10] > cost + 1) {
                d[nxt / 10] = cost + 1;
                pre[nxt / 10] = { i, digit };
                q.push({ nxt / 10, cost + 1 });
            }
        }
    }
    if(d[0] == INF || d[0] > 100) {
        cout << "BRAK\n";
        return;
    }

    string res;
    int cur = 0;
    while(pre[cur].first != -1) {
        res.push_back(pre[cur].second + '0');
        cur = cur * 10 + pre[cur].second - n * pre[cur].first;
    }
    res.push_back(pre[cur].second + '0');

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
