#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h
struct SuffixArray
{
    vector<int> sa, lcp;
    vector<int> ori, lg2;
    vector<vector<int>> st;

    SuffixArray(string& s, int lim = 256)
    {
        // or basic_string<int>
        int n = s.size() + 1, k = 0, a, b;
        vector<int> x(s.begin(), s.end()), y(n), ws(max(n, lim)), rank(n);
        x.push_back(0);
        sa = lcp = y, iota(sa.begin(), sa.end(), 0);
        for(int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(y.begin(), y.end(), n - j);
            for(int i = 0; i < n; ++i) if(sa[i] >= j) y[p++] = sa[i] - j;
            fill(ws.begin(), ws.end(), 0);
            for(int i = 0; i < n; ++i) ws[x[i]]++;
            for(int i = 1; i < lim; ++i) ws[i] += ws[i - 1];
            for(int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; ++i) {
                a = sa[i - 1], b = sa[i];
                x[b] = (y[a] == y[b] && a + j < n && b + j < n && y[a + j] == y[b + j]) ? p - 1 : p++;
            }
        }
        for(int i = 1; i < n; ++i) rank[sa[i]] = i;
        for(int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for(k && k--, j = sa[rank[i] - 1];
                i + k < n - 1 && j + k < n - 1 && s[i + k] == s[j + k]; k++);

        // lcp RMQ build
        lg2.resize(n + 1);
        lg2[0] = lg2[1] = 0;
        for(int i = 2; i <= n; ++i) {
            lg2[i] = lg2[i / 2] + 1;
        }

        ori.resize(n);
        int dep = lg2[n];
        st.resize(n);
        for(int i = 0; i < n; ++i) {
            ori[sa[i]] = i;
            st[i].resize(dep + 1);
            st[i][0] = lcp[i];
        }
        for(int j = 1; j <= dep; ++j) {
            for(int i = 0; i + (1 << (j - 1)) < n; ++i) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int get_lcp(int l, int r)
    {
        if(l == r) return sa.size() - l - 1;
        l = ori[l], r = ori[r];
        if(l > r) swap(l, r);
        int j = lg2[r - l];
        return min(st[l + 1][j], st[r - (1 << j) + 1][j]);
    }
};

// sa[0] = str.size(), sa.size() = str.size() + 1
// lcp[i] = lcp(sa[i - 1], sa[i]), lcp[0] = 0

struct Frac
{
    ll u, d;
    Frac(ll _u, ll _d)
    {
        ll g = gcd(_u, _d);
        u = _u / g;
        d = _d / g;
    }

    bool operator<(const Frac& rhs) const
    {
        return u * rhs.d < d* rhs.u;
    }
};

void solve()
{
    string str;
    cin >> str;
    int n = str.size();

    SuffixArray sa(str);

    Frac res(1, 1);

    struct Range
    {
        set<int> indices;
        int lcp, mn;
    };
    vector<Range> st;
    st.push_back({ {}, 0, INF });

    auto merge = [&]() {
        auto i1 = move(st.back().indices);
        int mn = st.back().mn;
        int lcp = st.back().lcp;
        st.pop_back();

        auto i2 = move(st.back().indices);
        mn = min(mn, st.back().mn);
        if(i1.size() < i2.size()) swap(i1, i2);

        for(int l : i2) {
            auto it = i1.lower_bound(l);
            if(it != i1.begin()) mn = min(mn, l - *prev(it));
            if(it != i1.end()) mn = min(mn, *it - l);
        }
        for(int l : i2) {
            i1.insert(l);
        }

        st.back().indices = move(i1);
        st.back().mn = mn;

        res = max(res, Frac(mn + lcp, mn));
    };

    for(int i = 1; i <= n; ++i) {
        while(st.back().lcp > sa.lcp[i]) {
            merge();
        }

        st.push_back({ { sa.sa[i] }, sa.lcp[i], INF });
    }
    while(st.size() > 1) merge();

    cout << res.u << "/" << res.d;
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
