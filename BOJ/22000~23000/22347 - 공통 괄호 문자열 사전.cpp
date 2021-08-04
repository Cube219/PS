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
ll k;
int d[500002];
int h[500002];
vector<int> hh[1000002];

void getlcp()
{
    for(int i = 0; i < n; ++i) {
        d[i] = 0;
    }

    int curlcp = n;
    int st = 1;
    while(sa.sa[st] >= n) st++;
    for(int i = st; i < n + m + 1; ++i) {
        int idx = sa.sa[i];
        if(idx >= n) {
            curlcp = n;
        } else {
            curlcp = min(curlcp, sa.lcp[i - 1]);
            d[idx] = max(d[idx], curlcp);
        }
    }

    st = n + m - 1;
    curlcp = n;
    while(sa.sa[st] >= n) st--;
    for(int i = st; i >= 0; --i) {
        int idx = sa.sa[i];
        if(idx >= n) {
            curlcp = n;
        } else {
            curlcp = min(curlcp, sa.lcp[i]);
            d[idx] = max(d[idx], curlcp);
        }
    }
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
        cin >> s1 >> s2 >> k;
        if(s1.size() > s2.size()) swap(s1, s2);
        n = s1.size(); m = s2.size();
        string s;
        s.append(s1);
        s.push_back('&');
        s.append(s2);
        sa.init(n + m + 1);
        sa.build(s);

        getlcp();

        int hmin = 0;
        h[0] = 0;
        for(int i = 1; i <= n; ++i) {
            h[i] = h[i - 1];
            if(s1[i - 1] == '(') h[i]++;
            else h[i]--;
            hmin = min(hmin, h[i]);
        }
        hmin--;
        for(int i = 0; i <= n; ++i) {
            h[i] -= hmin;
        }
        for(int i = 0; i <= n; ++i) {
            hh[h[i]].push_back(i);
        }

        int resl = -1, resr = -1;
        ll kk = k;
        int skip = 0;
        for(int i = 0; i < n + m + 1; ++i) {
            int idx = sa.sa[i];
            if(i > 0) {
                skip = min(skip, sa.lcp[i - 1]);
            }
            if(idx >= n) continue;

            int l = idx;
            int r = l + d[idx] - 1;
            l++; r++;

            int lh = h[l - 1];
            auto it = lower_bound(hh[lh - 1].begin(), hh[lh - 1].end(), l - 1);
            int newr;
            if(it == hh[lh - 1].end()) {
                newr = n;
            } else {
                newr = *it - 1;
            }
            r = min(r, newr);

            auto it2 = upper_bound(hh[lh].begin(), hh[lh].end(), r);
            if(it2 != hh[lh].begin()) {
                --it2;
                auto it3 = lower_bound(hh[lh].begin(), hh[lh].end(), l + skip);
                int num = it2 - it3 + 1;
                if(num <= 0) continue;
                if(kk <= num) {
                    resl = l;
                    resr = hh[lh][it3 - hh[lh].begin() + kk - 1];
                    break;
                } else {
                    kk -= num;
                }
                skip = r - l + 1;
            }
        }

        if(resl == -1) {
            cout << "-1\n";
        } else {
            for(int i = resl - 1; i <= resr - 1; ++i) {
                cout << s1[i];
            }
            cout << "\n";
        }

        for(int i = 0; i <= n; ++i) {
            hh[h[i]].clear();
        }
    }

    return 0;
}
