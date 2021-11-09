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

int n, m, t;
vector<int> g[100001], grev[100001];
bool c[100001];
SCC<100001> sc;
bool dirty[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> t;
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if(v == t) {
            c[u] = true;
        } else {
            g[u].emplace_back(v);
            grev[v].emplace_back(u);
        }
    }

    sc.init(g, n);
    sc.process();

    vector<int> res;
    for(int i = 0; i < sc.sccs.size(); ++i) {
        auto& scc = sc.sccs[i];
        if(scc[0] == t) continue;

        int num = 0, idx;
        for(int v : scc) {
            if(c[v] == true) {
                num++;
                idx = v;
            }
        }

        if(num == 1 && dirty[i] == false) {
            res.push_back(idx);
        }
        if(dirty[i] == true || num >= 1) {
            for(int v : scc) {
                for(int nxt : grev[v]) {
                    dirty[sc.sccIdx[nxt] - 1] = true;
                }
            }
        }
    }

    sort(res.begin(), res.end());
    cout << res.size() << "\n";
    for(int v : res) {
        cout << v << "\n";
    }

    return 0;
}
