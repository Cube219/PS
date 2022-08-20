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
    struct Node { int v, cnt; };
    vector<Node> d(n);
    for(auto& v : d) {
        cin >> v.v;
        int tmp = v.v;
        v.cnt = 0;
        while(tmp > 0) {
            v.cnt++;
            tmp /= 10;
        }
    }
    sort(d.begin(), d.end(), [](auto& l, auto& r) {
        if(l.cnt == r.cnt) return l.v > r.v;
        return l.cnt > r.cnt;
    });

    ll res = 0;
    vector<int> order(3);
    iota(order.begin(), order.end(), 0);
    do {
        ll v = 0;
        for(int i : order) {
            for(int j = 0; j < d[i].cnt; ++j) {
                v *= 10;
            }
            v += d[i].v;
        }
        res = max(res, v);
    } while(next_permutation(order.begin(), order.end()));

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
