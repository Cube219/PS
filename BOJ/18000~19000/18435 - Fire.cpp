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

struct FenwickRange
{
    int n;
    vector<ll> tmul, tadd;
    FenwickRange(int _n) : n(_n + 1), tmul(_n + 1, 0), tadd(_n + 1, 0) {}

    void update(int l, int r, ll v)
    {
        l++;
        r++;
        udtImpl(l, v, -v * (l - 1));
        udtImpl(r, -v, v * r);
    }

    void udtImpl(int pos, ll mul, ll add)
    {
        for(; pos < n; pos += (pos & -pos)) {
            tmul[pos] += mul;
            tadd[pos] += add;
        }
    }

    ll query(int pos)
    {
        pos++;
        ll mul = 0, add = 0;
        int st = pos;
        for(; pos > 0; pos -= (pos & -pos)) {
            mul += tmul[pos];
            add += tadd[pos];
        }
        return mul * st + add;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll> d(n);
    for(auto& v : d) cin >> v;
    struct Query
    {
        int l, r, idx;
    };
    vector<vector<Query>> qList(n + 1);
    for(int i = 0; i < q; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        l--; r--;
        qList[t].push_back({ l, r, i });
    }

    struct Stack
    {
        ll v;
        int idx;
    };
    vector<Stack> st;
    vector<int> l(n);
    st.push_back({ LNF, -(n + 1) });
    for(int i = 0; i < n; ++i) {
        while(st.back().v < d[i]) st.pop_back();
        l[i] = st.back().idx;
        st.push_back({ d[i], i });
    }

    vector<int> r(n);
    st.clear();
    st.push_back({ LNF, n });
    for(int i = n - 1; i >= 0; --i) {
        while(st.back().v <= d[i]) st.pop_back();
        r[i] = st.back().idx;
        st.push_back({ d[i], i });
    }

    FenwickRange fw1(n * 2), fw2(n);
    struct FWQuery
    {
        int l, r;
        ll v;
    };
    vector<vector<FWQuery>> fw1QList(n + 1), fw2QList(n + 1);
    auto applyTriangle = [&](int l, int r, ll v) {
        if(r < n - 1) {
            fw2QList[0].push_back({ r + 1, n - 1, v });
            if(r - l + 1 <= n) fw2QList[r - l + 1].push_back({ r + 1, n - 1, -v });
        }
        fw1QList[0].push_back({ l + n, n * 2 - 1, v });
        if(r - l + 1 <= n) fw1QList[r - l + 1].push_back({ l + n, n * 2 - 1, -v });
    };
    for(int i = 0; i < n; ++i) {
        applyTriangle(l[i] + 1, r[i] - 1, d[i]);
        if(l[i] + 1 < i) applyTriangle(l[i] + 1, i - 1, -d[i]);
        if(i < r[i] - 1) applyTriangle(i + 1, r[i] - 1, -d[i]);
    }

    vector<ll> res(q);
    for(int i = 0; i <= n; ++i) {
        for(auto& q : fw1QList[i]) fw1.update(q.l, q.r, q.v);
        for(auto& q : fw2QList[i]) fw2.update(q.l, q.r, q.v);

        for(auto& q : qList[i]) {
            ll v = fw1.query(q.r - i + n);
            if(q.l - i + n > 0) v -= fw1.query(q.l - i + n - 1);

            ll v2 = fw2.query(q.r);
            if(q.l > 0) v2 -= fw2.query(q.l - 1);

            res[q.idx] = v - v2;
        }
    }

    for(ll v : res) cout << v << "\n";
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
