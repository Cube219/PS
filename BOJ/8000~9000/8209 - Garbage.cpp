#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

char buf[1 << 17];
int bufsize, bufidx;

int read()
{
    if(bufidx >= bufsize) {
        bufsize = fread(buf, 1, sizeof(buf), stdin);
        bufidx = 0;
    }
    return buf[bufidx++];
}

int readint()
{
    int res = 0;
    while(1) {
        int v = read();
        if('0' <= v && v <= '9') {
            res = v - '0';
            break;
        }
    }
    while(1) {
        int v = read();
        if(v < '0' || '9' < v) break;
        res *= 10;
        res += v - '0';
    }
    return res;
}

struct Edge
{
    int nxt, revidx;
    bool use;
};

int n, m;
vector<Edge> g[100001];
vector<int> path;
bool comp[100001], has[100001];
int cidx[100001];

void addEdge(int u, int v)
{
    Edge e1 = { v, -1, false };
    Edge e2 = { u, -1, false };
    e1.revidx = g[v].size();
    e2.revidx = g[u].size();
    g[u].push_back(e1);
    g[v].push_back(e2);
}

void dfs(int cur)
{
    comp[cur] = true;
    int& i = cidx[cur];
    for(; i < g[cur].size(); i++) {
        Edge& e = g[cur][i];
        if(e.use == true) continue;

        e.use = true;
        g[e.nxt][e.revidx].use = true;
        dfs(e.nxt);
    }
    path.push_back(cur);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    n = readint();
    m = readint();
    for(int i = 0; i < m; ++i) {
        int u, v, a, b;
        u = readint();
        v = readint();
        a = readint();
        b = readint();
        u--; v--;
        if((a ^ b) != 0) {
            addEdge(u, v);
        }
    }

    for(int i = 0; i < n; ++i) {
        if((g[i].size() & 1) == 1) {
            cout << "NIE";
            return 0;
        }
    }

    vector<vector<int>> res;
    vector<int> st;
    for(int i = 0; i < n; ++i) {
        if(comp[i] == false) {
            path.clear();
            st.clear();

            dfs(i);
            for(int j = path.size() - 1; j >= 0; --j) {
                int node = path[j];
                if(has[node] == true) {
                    res.push_back({ node });
                    auto& cres = res.back();
                    while(st.back() != node) {
                        int nnode = st.back();
                        has[nnode] = false;
                        cres.push_back(nnode);
                        st.pop_back();
                    }
                    cres.push_back(st.back());
                    st.pop_back();
                }
                st.push_back(node);
                has[node] = true;
            }
            has[st.back()] = false;
        }
    }

    cout << res.size() << "\n";
    for(auto& cres : res) {
        cout << cres.size() - 1 << " ";
        for(int v : cres) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}
