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

template <int N>
struct SCC
{
    int d[N], dNum = 1;
    bool finish[N];
    vector<int> st;
    vector<vector<int>> sccs;
    int sccIdx[N];

    vector<int>* g;
    int n;

    void init(vector<int>* _g, int _n)
    {
        g = _g;
        n = _n;

        for(int i = 0; i < n; ++i) {
            finish[i] = false;
            sccIdx[i] = 0;
            d[i] = 0;
        }
        sccs.clear();
        st.clear();
        dNum = 1;
    }

    void process()
    {
        for(int i = 0; i < n; ++i) {
            if(d[i] == 0) dfs(i);
        }
    }

    int dfs(int cur)
    {
        d[cur] = dNum++;
        st.push_back(cur);

        int ret = d[cur];
        for(int nxt : g[cur]) {
            if(d[nxt] == 0) ret = min(ret, dfs(nxt));
            else if(finish[nxt] == false) ret = min(ret, d[nxt]);
        }

        if(ret == d[cur]) {
            sccs.push_back({});
            auto& scc = sccs.back();
            while(1) {
                int top = st.back();
                st.pop_back();

                scc.push_back(top);
                sccIdx[top] = sccs.size();
                finish[top] = true;

                if(top == cur) break;
            }
        }
        return ret;
    }
};

int n, m;
string str, buf;
int dna[10001];
vector<int> d[6001];
SCC<40004> scc;
vector<int> g[40004];

int rev(int v)
{
    if(v % 2 == 0) return v + 1;
    return v - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 0;
    while(1) {
        tt++;
        cin >> n >> m;
        if(n == 0) break;
        if(tt == 20) {
            tt = 20;
        }
        cin >> str;
        for(int i = 0; i < n; ++i) {
            if(str[i] == 'A') dna[i] = 0;
            else if(str[i] == 'G') dna[i] = 1;
            else if(str[i] == 'T') dna[i] = 2;
            else dna[i] = 3;

            g[i * 4].clear();
            g[i * 4 + 1].clear();
            g[i * 4 + 2].clear();
            g[i * 4 + 3].clear();
        }

        getline(cin, buf);
        for(int i = 0; i < m; ++i) {
            d[i].clear();
            getline(cin, buf);

            int idx = 0;
            while(idx < buf.size() && buf[idx] != ' ') idx++;
            if(idx == buf.size()) continue;

            idx++;
            int v = 0;
            while(idx < buf.size()) {
                if(buf[idx] == ' ') {
                    d[i].push_back(v);
                    v = 0;
                    idx++;
                    continue;
                }
                v *= 10;
                v += buf[idx] - '0';
                idx++;
            }
            d[i].push_back(v);
        }

        for(int i = 0; i < n - 1; ++i) {
            int l = i, r = i + 1;
            g[l * 2 + 1].push_back(r * 2);
            g[r * 2 + 1].push_back(l * 2);
        }
        // 0: ¾È ¹Ù²Þ / 1: ¹Ù²Þ
        // 0: down / 1: up
        for(int i = 0; i < m; ++i) {
            int num = d[i].size();
            for(int j = 0; j < num / 2; ++j) {
                int l = d[i][j], r = d[i][num - j - 1];
                if(dna[l] == dna[r]) {
                    g[l * 2].push_back(r * 2);
                    g[l * 2 + 1].push_back(r * 2 + 1);
                    g[r * 2].push_back(l * 2);
                    g[r * 2 + 1].push_back(l * 2 + 1);

                    g[n * 2 + l * 2].push_back(n * 2 + r * 2);
                    g[n * 2 + l * 2 + 1].push_back(n * 2 + r * 2 + 1);
                    g[n * 2 + r * 2].push_back(n * 2 + l * 2);
                    g[n * 2 + r * 2 + 1].push_back(n * 2 + l * 2 + 1);
                } else if(abs(dna[l] - dna[r]) == 2) {
                    if(dna[l] > dna[r]) swap(l, r);
                    // g[l * 2 + 1].push_back(r * 2 + 1);
                    // g[r * 2 + 1].push_back(l * 2 + 1);
                    g[l * 2].push_back(l * 2 + 1);
                    g[r * 2].push_back(r * 2 + 1);

                    g[n * 2 + l * 2].push_back(n * 2 + r * 2 + 1);
                    g[n * 2 + l * 2 + 1].push_back(n * 2 + r * 2);
                    g[n * 2 + r * 2].push_back(n * 2 + l * 2 + 1);
                    g[n * 2 + r * 2 + 1].push_back(n * 2 + l * 2);
                } else {
                    if(dna[l] > dna[r]) swap(l, r);
                    if(dna[l] == 0 && dna[r] == 3) swap(l, r);
                    g[l * 2 + 1].push_back(r * 2);
                    g[r * 2 + 1].push_back(l * 2);
                    g[l * 2].push_back(r * 2 + 1);
                    g[r * 2].push_back(l * 2 + 1);

                    g[l * 2 + 1].push_back(n * 2 + l * 2 + 1);
                    g[n * 2 + l * 2].push_back(l * 2);
                    g[r * 2 + 1].push_back(n * 2 + r * 2);
                    g[n * 2 + r * 2 + 1].push_back(r * 2);
                }
            }
        }

        scc.init(g, n * 4);
        scc.process();
        bool pos = true;
        for(int i = 0; i < n * 2; ++i) {
            if(scc.sccIdx[i * 2] == scc.sccIdx[i * 2 + 1]) {
                pos = false;
                break;
            }
        }

        if(pos == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
