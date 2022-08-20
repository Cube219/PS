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
    ll n, m, k;
    cin >> n >> m >> k;
    struct Node
    {
        ll v, dv;
    };
    vector<Node> a(n);
    for(auto& v : a) {
        cin >> v.v;
    }

    ll res = 0;
    for(int bit = 32; bit >= 0; --bit) {
        ll mask = (1LL << (bit + 1)) - 1;

        for(auto& v : a) {
            ll vv = v.v & mask;
            if(vv & (1LL << bit)) {
                v.dv = 0;
            } else {
                v.dv = (1LL << bit) - vv;
            }
            v.v = vv;
        }

        sort(a.begin(), a.end(), [](auto& l, auto& r) {
            return l.dv < r.dv;
        });

        vector<Node> nxt;
        ll use = 0;
        for(auto& v : a) {
            if(v.dv == 0) nxt.push_back(v);
            else {
                if(use + v.dv > m || nxt.size() >= k) break;
                nxt.push_back(v);
                use += v.dv;
            }
        }
        if(nxt.size() >= k) {
            m -= use;
            for(auto& v : nxt) {
                if(v.dv > 0) v.v = 0;
            }
            a = move(nxt);
            res |= (1LL << bit);
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
