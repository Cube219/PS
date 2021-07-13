#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[200001];
int c[200001];
int res[200001];

int d1, d2;
int len[200001], dep[200001];
int cnt[200001], curcnt;
vector<int> st;

void add(int node)
{
    int v = c[node];
    if(cnt[v] == 0) curcnt++;
    cnt[v]++;
}
void remove(int node)
{
    int v = c[node];
    if(cnt[v] == 1) curcnt--;
    cnt[v]--;
}

void dfs(int cur, int par, int curlen)
{
    len[cur] = curlen;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur, curlen + 1);
    }
}

int dfs2(int cur, int par)
{
    int r = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        r = max(r, dfs2(nxt, cur));
    }
    dep[cur] = r + 1;
    return r + 1;
}

struct Node
{
    int nxt;
    int dep;
};
void dfs3(int cur, int par)
{
    vector<Node> child;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        child.push_back({ nxt, dep[nxt] });
    }
    sort(child.begin(), child.end(), [](const Node& l, const Node& r) {
        return l.dep > r.dep;
    });

    if(child.size() > 0) {
        int maxdep = 0;
        if(child.size() > 1) maxdep = child[1].dep;
        for(auto& nx : child) {
            while(st.size() > 0 && len[st.back()] >= len[cur] - maxdep) {
                remove(st.back());
                st.pop_back();
            }
            st.push_back(cur);
            add(cur);
            dfs3(nx.nxt, cur);

            maxdep = child[0].dep;
        }
        while(st.size() > 0 && len[st.back()] >= len[cur] - maxdep) {
            remove(st.back());
            st.pop_back();
        }
    }
    res[cur] = max(res[cur], curcnt);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
        c[i]--;
    }

    dfs(0, -1, 0);
    int mx = -1, mxidx = 0;
    for(int i = 0; i < n; ++i) {
        if(mx < len[i]) {
            mx = len[i];
            mxidx = i;
        }
    }
    d1 = mxidx;
    dfs(mxidx, -1, 0);
    mx = -1; mxidx = 0;
    for(int i = 0; i < n; ++i) {
        if(mx < len[i]) {
            mx = len[i];
            mxidx = i;
        }
    }
    d2 = mxidx;

    dfs2(d1, -1);
    dfs3(d1, -1);


    dfs(d2, -1, 0);
    dfs2(d2, -1);
    dfs3(d2, -1);

    for(int i = 0; i < n; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
