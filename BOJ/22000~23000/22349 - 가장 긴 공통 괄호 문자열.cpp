#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

using ll = long long int;

template <int N>
struct SuffixArray
{
    struct Node
    {
        int idx;
        int r0, r1;
    };

    int sa[N], lcp[N], idx[N];
    Node d[N], tmp[N];
    int n, cl;

    void init(int _n)
    {
        for(int i = 0; i <= _n; ++i) {
            sa[i] = 0;
            lcp[i] = 0;
            idx[i] = 0;
        }
    }

    void build(const string& str)
    {
        n = str.size();
        cl = max(200, n + 3);

        for(int i = 0; i < n; ++i) {
            d[i].idx = i;
            d[i].r0 = str[i];
            if(i + 1 < n) d[i].r1 = str[i + 1];
            else d[i].r1 = -1;
        }
        st();

        for(int sz = 4; sz < n * 2; sz *= 2) {
            int rnk = 0;
            int prnk = d[0].r0;
            d[0].r0 = rnk;
            idx[d[0].idx] = 0;

            for(int i = 1; i < n; ++i) {
                if(d[i].r0 == prnk && d[i].r1 == d[i - 1].r1) {
                    prnk = d[i].r0;
                    d[i].r0 = rnk;
                } else {
                    prnk = d[i].r0;
                    d[i].r0 = ++rnk;
                }
                idx[d[i].idx] = i;
            }

            for(int i = 0; i < n; ++i) {
                int nidx = d[i].idx + sz / 2;
                d[i].r1 = (nidx < n) ? d[idx[nidx]].r0 : -1;
            }
            st();
        }

        for(int i = 0; i < n; ++i) {
            sa[i] = d[i].idx;
        }

        // lcp
        for(int i = 0; i < n; ++i) {
            idx[sa[i]] = i;
        }
        int len = 0;
        for(int i = 0; i < n; ++i) {
            int c0 = idx[i];
            if(c0 == n - 1) continue;
            int c1 = sa[c0 + 1];
            while(str[i + len] == str[c1 + len]) {
                len++;
            }
            lcp[c0] = len;
            len = max(len - 1, 0);
        }
    }

    void st()
    {
        sort(d, d + n, [](const Node& l, const Node& r) {
            if(l.r0 == r.r0) return l.r1 < r.r1;
            return l.r0 < r.r0;
        });
    }
};

struct Node
{
    int l, r;
};

int tNum;
SuffixArray<1000010> sa;
string s1, s2;
int n, m;
vector<int> d;
int h[500001];
vector<int> hh[1000001];

void p()
{
    d.clear();
    d.resize(n, 0);
    // d의 idx는 idx에서 시작하는 suffix의 B-lcp
    int curlcp = n;
    int st = 0;
    while(sa.sa[st] >= n) st++;
    for(int i = st; i < n + m + 1; ++i) {
        int idx = sa.sa[i];
        if(idx >= n) {
            // B string
            curlcp = n;
        } else {
            // A string
            curlcp = min(curlcp, sa.lcp[i - 1]);
            d[idx] = max(d[idx], curlcp);
        }
    }

    curlcp = n + m + 1;
    st = n + m;
    while(sa.sa[st] >= n) st--;
    for(int i = st; i >= 0; --i) {
        int idx = sa.sa[i];
        if(idx >= n) {
            // B string
            curlcp = n;
        } else {
            // A string
            curlcp = min(curlcp, sa.lcp[i]);
            d[idx] = max(d[idx], curlcp);
        }
    }
}

int get(int l, int r)
{
    l++; r++;

    int hl = h[l - 1];
    int newr;
    auto it = lower_bound(hh[hl - 1].begin(), hh[hl - 1].end(), l - 1);
    if(it == hh[hl - 1].end()) {
        newr = n;
    } else {
        newr = *it - 1;
    }
    r = min(r, newr);
    auto it2 = upper_bound(hh[hl].begin(), hh[hl].end(), r);
    if(it2 == hh[hl].begin()) return 0;
    --it2;
    return *it2 - l + 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> s1 >> s2;
        if(s1.size() > s2.size()) swap(s1, s2);
        n = s1.size(); m = s2.size();
        string s;
        s.append(s1);
        s.push_back('&');
        s.append(s2);
        sa.init(n + m + 1);
        sa.build(s);

        p();

        int hmin = 0;
        for(int i = 1; i <= n; ++i) {
            h[i] = h[i - 1];
            if(s1[i - 1] == '(') h[i]++;
            else h[i]--;

            hmin = min(hmin, h[i]);
        }
        hmin--;
        for(int i = 0; i <= n; ++i) {
            h[i] -= hmin;
            hh[h[i]].push_back(i);
        }

        int res = 0;
        for(int i = 0; i < n; ++i) {
            res = max(res, get(i, i + d[i] - 1));
        }
        cout << res << "\n";

        for(int i = 0; i <= n; ++i) {
            hh[h[i]].clear();
        }
    }

    return 0;
}
