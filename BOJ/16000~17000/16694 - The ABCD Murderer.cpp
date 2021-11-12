#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct AhoCorasick
{
    enum { alpha = 26, first = 'a' };
    struct Node
    {
        int back, next[alpha], start = -1, end = -1;
        Node(int v)
        {
            memset(next, v, sizeof(next));
        }
    };
    vector<Node> N;
    vector<int> backp;
    void insert(string& s, int j)
    {
        int n = 0;
        for(char c : s) {
            int& m = N[n].next[c - first];
            if(m == -1) { n = m = N.size(); N.emplace_back(-1); } else n = m;
        }
        if(N[n].end == -1) N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
    }
    AhoCorasick(vector<string>& pat) : N(1, -1)
    {
        for(int i = 0; i < pat.size(); ++i) {
            insert(pat[i], i);
        }
        N[0].back = N.size();
        N.emplace_back(0);

        queue<int> q;
        for(q.push(0); !q.empty(); q.pop()) {
            int n = q.front(), prev = N[n].back;
            for(int i = 0; i < alpha; ++i) {
                int& ed = N[n].next[i], y = N[prev].next[i];
                if(ed == -1) ed = y;
                else {
                    N[ed].back = y;
                    (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
                    q.push(ed);
                }
            }
        }
    }
    vector<int> find(const string& word)
    {
        int n = 0;
        vector<int> res;
        for(char c : word) {
            n = N[n].next[c - first];
            res.push_back(N[n].end);
        }
        return res;
    }
    vector<vector<int>> findAll(vector<string>& pat, const string& word)
    {
        vector<int> r = find(word);
        vector<vector<int>> res(word.size());
        for(int i = 0; i < word.size(); ++i) {
            int ind = r[i];
            while(ind != -1) {
                res[i - pat[ind].size() + 1].push_back(ind);
                ind = backp[ind];
            }
        }
        return res;
    }
};

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

    void build()
    {
        for(int i = n - 1; i > 0; --i) {
            t[i] = merge(t[i << 1], t[i << 1 | 1]);
        }
    }

    void update(int idx, int v)
    {
        idx += n;
        t[idx] = v;
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
        int resl = INF;
        int resr = INF;
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
        return min(l, r);
    }
};

int n;
vector<string> pat;
string str;
ll dp[300001];
SegTree<300002> sg;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cin >> str;
    pat.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> pat[i];
    }
    AhoCorasick ac(pat);

    auto res = ac.find(str);

    int m = str.size();

    sg.init(m + 1);
    for(int i = 1; i <= m; ++i) {
        sg.t[m + 1 + i] = INF;
        dp[i] = -1;
    }
    sg.build();

    for(int i = 1; i <= m; ++i) {
        if(res[i - 1] == -1) continue;
        int sz = pat[res[i - 1]].size();
        int v = sg.find(i - sz, i - 1);
        if(v < INF) {
            dp[i] = v + 1;
            sg.update(i, v + 1);
        }
    }

    cout << dp[m];

    return 0;
}
