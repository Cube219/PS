#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

struct SuffixTree
{
    struct Node
    {
        int nxt[27];
        int l, r, p, suf;
        int link;
        Node()
        {
            l = 0;
            r = 0;
            p = 0;
            link = 0;
            suf = 0;
            for(int i = 0; i < 27; ++i) {
                nxt[i] = 0;
            }
        }
    };
    vector<Node> t;
    int curNode, curPos;

    int ctoi(char ch)
    {
        if(ch == '$') return 26;
        return ch - 'a';
    }

    void build(const string& str)
    {
        curNode = 1;
        curPos = 0;
        t.clear();
        t.push_back({});
        t.push_back({});
        t[1].l = -1;
        for(int i = 0; i < 27; ++i) {
            t[0].nxt[i] = 1;
        }

        int n = str.size();
        for(int i = 0; i < n; ++i) {
            add(str, i);
        }
    }

    void add(const string& str, int idx)
    {
        int ch = ctoi(str[idx]);
        go:
        if(t[curNode].r <= curPos) {
            if(t[curNode].nxt[ch] == 0) {
                Node leaf;
                leaf.p = curNode;
                leaf.l = idx;
                leaf.r = str.size();
                t[curNode].nxt[ch] = t.size();
                t.push_back(leaf);

                curNode = t[curNode].suf;
                curPos = t[curNode].r;
                goto go;
            }
            curNode = t[curNode].nxt[ch];
            curPos = t[curNode].l + 1;
        } else if(str[idx] == str[curPos]) {
            curPos++;
        } else {
            Node innode;
            int innodeidx = t.size();
            innode.l = t[curNode].l;
            innode.r = curPos;
            innode.p = t[curNode].p;
            t.push_back(innode);
            t[curNode].l = curPos;
            t[curNode].p = innodeidx;
            t[t[innodeidx].p].nxt[ctoi(str[t[innodeidx].l])] = innodeidx;
            t[innodeidx].nxt[ctoi(str[curPos])] = curNode;

            Node leaf;
            leaf.p = t.size() - 1;
            leaf.l = idx;
            leaf.r = str.size();
            t[innodeidx].nxt[ch] = t.size();
            t.push_back(leaf);

            curNode = t[t[innodeidx].p].suf;
            curPos = t[innodeidx].l;
            while(curPos < t[innodeidx].r) {
                curNode = t[curNode].nxt[ctoi(str[curPos])];
                curPos += t[curNode].r - t[curNode].l;
            }
            t[innodeidx].suf = (curPos == t[innodeidx].r) ? curNode : t.size();
            curPos = t[curNode].r - (curPos - t[innodeidx].r);

            goto go;
        }
    }
};

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
        return u * rhs.d < d * rhs.u;
    }

    ll gcd(ll a, ll b)
    {
        if(a < b) swap(a, b);
        if(b == 0) return a;
        return gcd(b, a % b);
    }
};

string str;
SuffixTree st;
Frac res(1, 1);
set<int> lens[500001];

int dfs(int cur, int len)
{
    // Leaf node
    if(st.t[cur].r == str.size()) {
        lens[cur].insert(len);
        return str.size();
    }

    int ret = str.size();
    for(int i = 0; i < 27; ++i) {
        int nxt = st.t[cur].nxt[i];
        if(nxt == 0) continue;
        ret = min(ret, dfs(nxt, len + st.t[nxt].r - st.t[nxt].l));
        if(lens[cur] < lens[nxt]) {
            swap(lens[cur], lens[nxt]);
        }
        for(int nlen : lens[nxt]) {
            auto it = lens[cur].lower_bound(nlen);
            if(it != lens[cur].end()) {
                ret = min(ret, *it - nlen);
            }
            if(it != lens[cur].begin()) {
                --it;
                ret = min(ret, nlen - *it);
            }

            lens[cur].insert(nlen);
        }
    }

    if(ret < str.size()) {
        res = max(res, Frac(len + ret, ret));
    }
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;
    str += '$';
    st.build(str);

    for(int i = 0; i < 26; ++i) {
        int nxt = st.t[1].nxt[i];
        if(nxt != 0) {
            dfs(nxt, st.t[nxt].r - st.t[nxt].l);
        }
    }

    cout << res.u << "/" << res.d;

    return 0;
}
