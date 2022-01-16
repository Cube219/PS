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
        int l, r, v;
    };
    vector<Node> d(n);
    for(auto& v : d) {
        cin >> v.l >> v.r >> v.v;
    }

    int res = 0;
    for(int i = 0; i < n; ++i) {
        vector<pair<double, int>> time;

        int pos = d[i].l;

        for(int j = 0; j < n; ++j) {
            if(i == j) continue;

            double st = -1, ed;
            int v = d[i].v - d[j].v;
            if(pos < d[j].l) {
                if(v > 0) {
                    st = (double)(d[j].l - pos) / v;
                    ed = (double)(d[j].r - pos) / v;
                }
            } else if(d[j].r < pos) {
                if(v < 0) {
                    st = (double)(pos - d[j].r) / (-v);
                    ed = (double)(pos - d[j].l) / (-v);
                }
            } else {
                st = 0;
                if(v > 0) {
                    ed = (double)(d[j].r - pos) / v;
                } else if(v < 0) {
                    ed = (double)(pos - d[j].l) / (-v);
                } else {
                    ed = INF;
                }
            }
            if(st < 0) continue;
            time.push_back({ st, 1 });
            time.push_back({ ed, -1 });
        }
        sort(time.begin(), time.end(), [](const auto& l, const auto& r) {
            if(l.first == r.first) return l.second > r.second;
            return l.first < r.first;
        });

        int r = 0, cur = 0;
        for(auto& t : time) {
            r = max(r, cur);
            cur += t.second;
        }

        res = max(res, r + 1);
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
