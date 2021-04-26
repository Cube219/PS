#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n;
vector<int> g[200001];
int dep[200001], sz[200001];
bool visit[200001];
int res[200001];

int dfs2(int cur, int par)
{
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        sz[cur] += dfs2(nxt, cur);
    }
    return sz[cur];
}

int num = 1;
int dfs(int cur, int par, int dep)
{
    res[cur] = num++;
    int ret = dep;

    int maxSz = -1, maxNode = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        if(maxSz < sz[nxt]) {
            maxSz = sz[nxt];
            maxNode = nxt;
        }
    }

    for(int nxt : g[cur]) {
        if(nxt == par || nxt == maxNode) continue;
        ret = max(ret, dfs(nxt, cur, dep + 1));
        num += ret - dep;
    }
    if(maxNode != 0) {
        ret = max(ret, dfs(maxNode, cur, dep + 1));
    }
    num += ret - dep;

    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int maxdep = -1, maxnode = 0;
    queue<int> q;
    q.push(1);
    visit[1] = true;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        if(maxdep < dep[cur]) {
            maxdep = dep[cur];
            maxnode = cur;
        }
        for(int nxt : g[cur]) {
            if(visit[nxt] == true) continue;
            q.push(nxt);
            dep[nxt] = dep[cur] + 1;
            visit[nxt] = true;
        }
    }
    for(int i = 1; i <= n; ++i) {
        dep[i] = 0;
        visit[i] = false;
    }
    q.push(maxnode);
    visit[maxnode] = true;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        for(int nxt : g[cur]) {
            if(visit[nxt] == true) continue;
            q.push(nxt);
            dep[nxt] = dep[cur] + 1;
            visit[nxt] = true;
        }
    }

    dfs2(maxnode, -1);
    dfs(maxnode, -1, 0);

    for(int i = 1; i <= n; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
