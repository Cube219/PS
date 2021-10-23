#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

struct KMP
{
    vector<int> fail;

    void init_fail(const string& w)
    {
        int wn = w.size();
        fail.clear();
        fail.resize(wn, 0);

        int j = 0;
        for(int i = 1; i < wn; ++i) {
            while(j > 0 && w[i] != w[j]) {
                j = fail[j - 1];
            }
            if(w[i] == w[j]) {
                fail[i] = j + 1;
                j++;
            }
        }
    }

    void get(const string& s, const string& w, vector<int>& res)
    {
        init_fail(w);
        res.clear();
        res.resize(s.size(), 0);

        int sn = s.size();
        int wn = w.size();

        int j = 0;
        for(int i = 0; i < sn; ++i) {
            while(j > 0 && s[i] != w[j]) {
                j = fail[j - 1];
            }
            if(s[i] == w[j]) {
                res[i - j] = j + 1;
                if(j == wn - 1) {
                    j = fail[j];
                } else {
                    j++;
                }
            }
        }
    }
};

struct Node
{
    int len;
    int r1, r2;
};

string s1, s2;
int n, m;
int ss[2][3001];
int sp[3001], ps[3001];
KMP kmp;

Node process()
{
    Node res = { 0, 0, 0 };

    for(int j = 0; j < m; ++j) {
        ss[0][j] = 0;
    }
    for(int j = 0; j < m; ++j) {
        if(s1[0] == s2[j]) {
            ss[0][j] = 1;
            res.len = 1;
            res.r1 = 0;
            res.r2 = j;
        }
    }

    for(int i = 1; i < n; ++i) {
        int cur = i % 2;
        int pre = 1 - cur;
        for(int j = 0; j < m; ++j) {
            ss[cur][j] = 0;
            sp[j] = 0;
            ps[j] = 0;
        }

        if(s1[i] == s2[0]) {
            ss[cur][0] = 1;
        }
        for(int j = 1; j < m; ++j) {
            if(s1[i] == s2[j]) {
                ss[cur][j] = ss[pre][j - 1] + 1;
            }
        }
        for(int j = 1; j < m; ++j) {
            int len = ss[cur][j];
            sp[j - len + 1] = max(sp[j - len + 1], len);
        }
        for(int j = 1; j < m; ++j) {
            sp[j] = max(sp[j], sp[j - 1] - 1);
        }

        string w = s1.substr(i + 1);
        vector<int> p;
        kmp.get(s2, w, p);
        for(int j = 0; j < m; ++j) {
            int len = p[j];
            ps[j + len - 1] = max(ps[j + len - 1], p[j]);
        }
        for(int j = m - 1; j >= 0; --j) {
            ps[j] = max(ps[j], ps[j + 1] - 1);
        }

        if(sp[0] > res.len) {
            res.len = sp[0];
            res.r1 = i - sp[0] + 1;
            res.r2 = 0;
        }
        for(int j = 0; j < m; ++j) {
            int l1 = sp[j + 1];
            int l2 = ps[j];
            if(res.len < l1 + l2) {
                res.len = l1 + l2;
                res.r1 = i - l1 + 1;
                res.r2 = j - l2 + 1;
            }
        }
    }

    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s1 >> s2;
    n = s1.size();
    m = s2.size();

    auto r1 = process();
    reverse(s2.begin(), s2.end());
    auto r2 = process();
    if(r1.len < r2.len) swap(r1, r2);
    cout << r1.len << "\n";
    cout << r1.r1 << " " << r1.r2;

    return 0;
}
