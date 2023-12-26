#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct SegTree
{
    using T = ll;
    T merge(T l, T r)
    {
        return max(l, r);
    }
    const T emptyNode = 0;

    vector<T> t;
    vector<ll> lazy;
    int n;

    SegTree(int _n)
    {
        n = 1;
        while (n < _n) n <<= 1;

        t.resize(n << 1, emptyNode);
        lazy.resize(n << 1, 0);
    }

    void initv(int idx, T v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for (int i = n - 1; i > 0; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void clear()
    {
        fill(t.begin(), t.end(), emptyNode);
        fill(lazy.begin(), lazy.end(), 0);
    }

    void push(int l, int r, int node)
    {
        if (lazy[node] == 0) return;

        if (node < n) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        t[node] += lazy[node];
        lazy[node] = 0;
    }

    T _qry(int cl, int cr, int l, int r, int node)
    {
        push(cl, cr, node);
        if (cr < l || r < cl) return emptyNode;
        if (l <= cl && cr <= r) return t[node];
        int m = (cl + cr) >> 1;
        return merge(_qry(cl, m, l, r, node << 1),
                     _qry(m + 1, cr, l, r, node << 1 | 1));
    }

    void _udt(int cl, int cr, int l, int r, int node, T v)
    {
        push(cl, cr, node);
        if (cr < l || r < cl) return;
        if (l <= cl && cr <= r) {
            lazy[node] += v;
            push(cl, cr, node);
            return;
        }
        int m = (cl + cr) >> 1;
        _udt(cl, m, l, r, node << 1, v);
        _udt(m + 1, cr, l, r, node << 1 | 1, v);
        t[node] = merge(t[node << 1], t[node << 1 | 1]);
    }

    T query(int l, int r)
    {
        return _qry(0, n - 1, l, r, 1);
    }

    void update(int l, int r, T v)
    {
        if (l > r) return;

        _udt(0, n - 1, l, r, 1, v);
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> d(n + 1, vector<ll>(m, 0LL));
    for (int i = 0; i < n; ++i) {
        for (auto& v2 : d[i]) cin >> v2;
    }

    int mm = m - k + 1;
    vector<vector<ll>> d2(n, vector<ll>(mm));
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j < k - 1; ++j) {
            sum += d[i][j] + d[i + 1][j];
        }

        for (int j = 0; j < mm; ++j) {
            sum += d[i][j + k - 1] + d[i + 1][j + k - 1];
            d2[i][j] = sum;
            sum -= d[i][j] + d[i + 1][j];
        }
    }

    vector<ll> dp(mm), nxt(mm);
    for (int i = 0; i < mm; ++i) {
        dp[i] = d2[0][i];
    }

    SegTree sg(mm);
    for (int i = 1; i < n; ++i) {
        sg.clear();
        ll sum = 0;
        for (int j = k - 1; j >= 0; j--) {
            sum += d[i][j];
            if (j < mm) sg.initv(j, dp[j] - sum);
        }
        for (int j = k; j < mm; ++j) {
            sg.initv(j, dp[j]);
        }
        sg.build();

        for (int j = 0; j < mm; ++j) {
            nxt[j] = sg.query(0, mm - 1) + d2[i][j];

            sg.update(max(0, j - k + 1), j, d[i][j]);
            sg.update(j + 1, min(mm - 1, j + k), -d[i][j + k]);
        }

        swap(dp, nxt);
    }

    cout << *max_element(dp.begin(), dp.end());
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
