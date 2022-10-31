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

struct MST
{
    int n;
    vector<vector<ll>> t;
    MST(int _n) : n(_n), t(_n * 2) {}

    void initv(int idx, ll v)
    {
        t[n + idx].push_back(v);
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            auto& lt = t[i << 1];
            auto& rt = t[i << 1 | 1];
            t[i].reserve(lt.size() + rt.size());

            int li = 0, ri = 0;
            while(li < lt.size() && ri < rt.size()) {
                if(lt[li] < rt[ri]) t[i].push_back(lt[li++]);
                else t[i].push_back(rt[ri++]);
            }
            for(; li < lt.size(); ++li) t[i].push_back(lt[li]);
            for(; ri < rt.size(); ++ri) t[i].push_back(rt[ri]);
        }
    }

    ll getMin(vector<ll>& cur, ll v)
    {
        int idx = lower_bound(cur.begin(), cur.end(), -v) - cur.begin();
        ll res = LNF;
        if(idx < cur.size()) res = min(res, abs(cur[idx] + v));
        if(idx > 0) res = min(res, abs(cur[idx - 1] + v));
        return res;
    }

    ll query(int l, int r, ll v)
    {
        ll res = LNF;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = min(res, getMin(t[l++], v));
            if(r & 1) res = min(getMin(t[--r], v), res);
        }
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<ll> d(n), sum(n);
    for(auto& v : d) cin >> v;

    partial_sum(d.begin(), d.end(), sum.begin());
    auto getSum = [&](int l, int r) {
        ll res = sum[r];
        if(l > 0) res -= sum[l - 1];
        return res;
    };
    MST mst(n);
    for(int i = 1; i < n; ++i) {
        mst.initv(i, sum[i - 1] * 2);
    }
    mst.build();

    int qNum;
    cin >> qNum;
    for(int i = 0; i < qNum; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        int sz = (r - l + 1) / 3;
        ll lSum = getSum(l, l + sz - 1);
        ll rSum = getSum(r - sz + 1, r);

        ll v = lSum - rSum - sum[l + sz - 1] - sum[r - sz];
        cout << mst.query(l + sz, r - sz + 1, v) << "\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
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
