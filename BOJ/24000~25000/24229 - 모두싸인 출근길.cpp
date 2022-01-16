#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    struct Line
    {
        int l, r;
    };
    int n;
    cin >> n;
    vector<Line> d(n);
    for(auto& v : d) cin >> v.l >> v.r;

    sort(d.begin(), d.end(), [](const Line& l, const Line& r) {
        if(l.r == r.r) return l.l < r.l;
        return l.r < r.r;
    });

    vector<Line> d2;

    for(auto& line : d) {
        int minl = INF;
        while(d2.size() > 0 && d2.back().r >= line.l) {
            minl = min(minl, d2.back().l);
            d2.pop_back();
        }
        d2.push_back({ min(minl, line.l), line.r });
    }

    vector<int> res(d2.size());
    for(int i = d2.size() - 1; i >= 0; --i) {
        Line cur = d2[i];

        int dis = cur.r - cur.l;
        res[i] = cur.r;
        for(int j = i; j < d2.size(); ++j) {
            if(cur.r + dis < d2[j].l) break;
            res[i] = max(res[i], res[j]);
        }
    }

    cout << res[0];
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
