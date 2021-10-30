#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

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

int n;
string str;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;

    SuffixArray sa(str);
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        res = max(res, sa.lcp[i]);
    }
    cout << res;

    return 0;
}
