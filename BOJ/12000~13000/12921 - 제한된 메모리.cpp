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
    ll n, x0, a, b, q;
    cin >> n >> x0 >> a >> b >> q;
    vector<int> qList(q), lo(q, -1), hi(q, 1'000'000'007);
    for(auto& v : qList) cin >> v;

    struct Node
    {
        int mid;
        int idx;
    };
    while(1) {
        vector<Node> d;
        vector<int> midList;
        for(int i = 0; i < q; ++i) {
            if(lo[i] + 1 == hi[i]) continue;
            d.push_back({ (lo[i] + hi[i]) / 2, i });
            midList.push_back((lo[i] + hi[i]) / 2);
        }
        if(midList.size() == 0) break;
        sort(midList.begin(), midList.end());
        midList.erase(unique(midList.begin(), midList.end()), midList.end());

        ll x = x0;
        vector<int> cnt(midList.size(), 0);
        for(int i = 0; i < n; ++i) {
            int idx = upper_bound(midList.begin(), midList.end(), x) - midList.begin();
            if(idx < midList.size()) cnt[idx]++;
            x = (x * a + b) % 1'000'000'007;
        }

        for(int i = 1; i < cnt.size(); ++i) {
            cnt[i] += cnt[i - 1];
        }
        for(auto& v : d) {
            int idx = lower_bound(midList.begin(), midList.end(), v.mid) - midList.begin();
            int c = cnt[idx];
            if(c > qList[v.idx]) {
                hi[v.idx] = midList[idx];
            } else {
                lo[v.idx] = midList[idx];
            }
        }
    }

    ll res = 0;
    for(int i = 0; i < q; ++i) {
        res += lo[i];
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
