#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <int N>
struct SegTree
{
    int n;
    int t[N * 2 + 1];

    void init(int _n)
    {
        n = _n;
        // Add init values in [n, n+n)
    }

    void clear()
    {
        for(int i = 1; i < n * 2; ++i) {
            t[i] = 0;
        }
    }

    void update(int idx, int v)
    {
        idx += n;
        t[idx] += v;
        idx >>= 1;
        while(idx > 0) {
            t[idx] = merge(t[idx << 1], t[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    int find(int l, int r)
    {
        l += n;
        r += n + 1;
        int resl = 0;
        int resr = 0;
        while(l < r) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
            l >>= 1;
            r >>= 1;
        }
        return merge(resl, resr);
    }

    int merge(int l, int r)
    {
        return l + r;
    }
};

int n, m;
vector<int> a, b, tmp;
vector<int> bb;

struct KMP
{
    vector<int> fail;
    vector<int> lcnt, gcnt;
    SegTree<1000001> sg;

    bool issame(int pos, int v, int mx)
    {
        if(lcnt[pos] != sg.find(0, v - 1)) return false;
        if(gcnt[pos] != sg.find(v + 1, mx - 1)) return false;
        return true;
    }

    void init_fail(const vector<int>& w)
    {
        int wn = w.size();
        fail.clear();
        fail.resize(wn, 0);
        sg.init(n);
        sg.clear();
        lcnt.resize(wn, 0); gcnt.resize(wn, 0);
        for(int i = 0; i < wn; ++i) {
            lcnt[i] = sg.find(0, w[i] - 1);
            gcnt[i] = sg.find(w[i] + 1, n - 1);
            sg.update(w[i], 1);
        }

        sg.clear();
        int j = 0;
        for(int i = 1; i < wn; ++i) {
            while(j > 0 && issame(j, w[i], n) == false) {
                int gap = j - fail[j - 1];
                for(int k = i - j; k < i - j + gap; ++k) {
                    sg.update(w[k], -1);
                }
                j = fail[j - 1];
            }
            if(issame(j, w[i], n) == true) {
                sg.update(w[i], 1);
                fail[i] = j + 1;
                j++;
            }
        }
    }

    void get(const vector<int>& s, const vector<int>& w, vector<int>& res)
    {
        init_fail(w);
        res.clear();

        int sn = s.size();
        int wn = w.size();
        
        sg.init(bb.size());
        sg.clear();
        int j = 0;
        for(int i = 0; i < sn; ++i) {
            while(j > 0 && issame(j, s[i], bb.size()) == false) {
                int gap = j - fail[j - 1];
                for(int k = i - j; k < i - j + gap; ++k) {
                    sg.update(s[k], -1);
                }
                j = fail[j - 1];
            }
            if(issame(j, s[i], bb.size()) == true) {
                sg.update(s[i], 1);
                j++;
            }
            if(j == wn) {
                res.push_back(i - wn + 1);
                int gap = j - fail[j - 1];
                for(int k = i - j + 1; k < i - j + 1 + gap; ++k) {
                    sg.update(s[k], -1);
                }
                j = fail[j - 1];
            }
        }
    }
};

int getb(int v)
{
    return lower_bound(bb.begin(), bb.end(), v) - bb.begin();
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    a.resize(n); tmp.resize(n); b.resize(m);
    for(int i = 0; i < n; ++i) {
        cin >> tmp[i];
        a[tmp[i] - 1] = i;
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
        bb.push_back(b[i]);
    }
    sort(bb.begin(), bb.end());
    bb.erase(unique(bb.begin(), bb.end()), bb.end());
    for(int i = 0; i < m; ++i) {
        b[i] = getb(b[i]);
    }

    KMP kmp;
    vector<int> res;
    kmp.get(b, a, res);

    cout << res.size() << "\n";
    for(int v : res) cout << v + 1 << " ";

    return 0;
}
