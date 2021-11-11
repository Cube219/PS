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

struct AhoCorasic
{
    enum { alpha = 26, first = 'a' };
    struct Node{
        int back, next[alpha], start = -1, end = -1, nmatches = 0;
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
        for(char c:s) {
            int& m = N[n].next[c - first];
            if(m == -1) { n = m = N.size(); N.emplace_back(-1); }
            else n = m;
        }
        if(N[n].end == -1) N[n].start = j;
        backp.push_back(N[n].end);
        N[n].end = j;
        N[n].nmatches++;
    }
    AhoCorasic(vector<string>& pat) : N(1, -1)
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
                    N[ed].nmatches += N[y].nmatches;
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

constexpr ll MOD = 1000000007;

int n;
vector<string> pat;
string str;
ll dp[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    pat.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> pat[i];
    }
    cin >> str;
    AhoCorasic ac(pat);

    auto res = ac.findAll(pat, str);

    int m = str.size();
    dp[m] = 1;
    for(int i = m - 1; i >= 0; --i) {
        for(int idx : res[i]) {
            int sz = pat[idx].size();
            if(i + sz > m) break;
            dp[i] = (dp[i] + dp[i + sz]) % MOD;
        }
    }

    cout << dp[0];

    return 0;
}
