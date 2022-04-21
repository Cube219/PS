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

void solve()
{
    int n;
    cin >> n;
    struct Node
    {
        int x, y;
        double angle;
    };
    vector<Node> d(n);
    for(auto& v : d) {
        cin >> v.x >> v.y;
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        if(l.x == r.x) return l.y < r.y;
        return l.x < r.x;
    });

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        auto [x, y, _] = d[i];

        vector<Node> d2;
        for(int j = i + 1; j < n; ++j) {
            auto [x2, y2, _] = d[j];
            d2.push_back({ x2, y2, (double)(y2 - y) / (x2 - x) });
        }

        sort(d2.begin(), d2.end(), [](const Node& l, const Node& r) {
            return l.angle < r.angle;
        });

        ll xsum = 0, ysum = 0;
        for(auto [x2, y2, _] : d2) {
            x2 -= x;
            y2 -= y;
            res += xsum * y2 - x2 * ysum;
            xsum += x2;
            ysum += y2;
        }
    }

    cout << res / 2;
    if(res & 1) cout << ".5";
    else cout << ".0";
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
