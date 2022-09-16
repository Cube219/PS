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

// https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/SuffixArray.h
struct SuffixArray
{
    vector<int> sa, lcp;

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
    }
};

// sa[0] = str.size(), sa.size() = str.size() + 1
// lcp[i] = lcp(sa[i - 1], sa[i]), lcp[0] = 0

// d1: ab c ba -> 00200
// d2: ab b a -> 0020
pair<vector<int>, vector<int>> manacher(const string& str)
{
    int n = str.size();
    vector<int> d1(n), d2(n);
    int l = 0, r = -1;
    for(int i = 0; i < n; ++i) {
        int k = 1;
        if(i <= r) {
            k = min(d1[l + r - i], r - i);
        }
        while(0 <= i - k && i + k < n && str[i - k] == str[i + k]) k++;
        d1[i] = --k;
        if(i + k > r) {
            r = i + k;
            l = i - k;
        }
    }

    l = 0;
    r = -1;
    for(int i = 0; i < n; ++i) {
        int k = 0;
        if(i <= r) {
            k = min(d2[l + r - i + 1], r - i);
        }
        while(0 <= i - k - 1 && i + k < n && str[i - k - 1] == str[i + k]) k++;
        d2[i] = k--;
        if(i + k > r) {
            r = i + k - 1;
            l = i - k;
        }
    }
    return { d1, d2 };
}

void solve()
{
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;

    vector<int> pal(n, INF);
    auto [odd, even] = manacher(str);
    for(int i = 0; i < n; ++i) {
        int req = k / 2;
        if(odd[i] >= req) {
            pal[i - req] = min(pal[i - req], req * 2 + 1);
        }
        req = (k + 1) / 2;
        if(even[i] >= req) {
            pal[i - req] = min(pal[i - req], req * 2);
        }
    }

    SuffixArray sa(str);
    vector<int> pos(n);
    for(int i = 1; i <= n; ++i) {
        pos[sa.sa[i]] = i;
    }

    ll res = 0;
    int pi = 0;
    for(int i = 0; i < n; ++i) {
        while(pi < n && (pal[pi] == INF || pi < i)) pi++;
        if(pi == n) break;

        int j = pos[i];
        int st = max(i + sa.lcp[j], pi + pal[pi] - 1);
        int v = max(0, n - st);
        res += v;
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
