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
    }
};
// sa[0] = str.size(), sa.size() = str.size() + 1
// lcp[i] = lcp(sa[i - 1], sa[i]), lcp[0] = 0

string specialStr = "!@#$%^&*()_-";

void solve()
{

    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    string str;
    cin >> str;

    SuffixArray sa(str);
    vector<int> saIdx(n);
    for(int i = 1; i <= n; ++i) saIdx[sa.sa[i]] = i;

    vector<int> st(n + 1, n + 1);
    int sz = 0, num = 0, special = 0, capital = 0;
    auto isOK = [&]() {
        if(sz >= a && num >= b && special >= c && capital >= d) return true;
        return false;
    };
    auto change = [&](int idx, int dv) {
        char ch = str[idx];
        if('0' <= ch && ch <= '9') num += dv;
        else if('A' <= ch && ch <= 'Z') capital += dv;
        for(char s : specialStr) {
            if(s == ch) {
                special += dv;
                break;
            }
        }
        sz += dv;
    };
    int r = 0;
    for(int l = 0; l < n; ++l) {
        while(r < n && isOK() == false) {
            change(r, 1);
            r++;
        }
        if(isOK()) st[saIdx[l]] = r - 1;
        change(l, -1);
    }

    for(int i = 2; i <= n; ++i) {
        st[i] = max(st[i], sa.sa[i] + sa.lcp[i]);
    }

    ll m = 0;
    for(int i = 1; i <= n; ++i) {
        m += max(0, n - st[i]);
    }

    m = (m + 1) / 2;
    for(int i = 1; i <= n; ++i) {
        int num = max(0, n - st[i]);
        if(num < m) {
            m -= num;
            continue;
        }

        int r = st[i] + m - 1;
        for(int j = sa.sa[i]; j <= r; ++j) {
            cout << str[j];
        }
        break;
    }
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
