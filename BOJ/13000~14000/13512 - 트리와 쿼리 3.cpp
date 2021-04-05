#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[100001];

int parent[100001], sz[100001];
int ch[100001], chIdx[100001];
vector<vector<int>> chList;
int chFirst[100001], chDepth[100001], num;
vector<set<int>> chWhiteList;
bool isWhite[100001];

int dfs(int cur, int p)
{
    parent[cur] = p;
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        sz[cur] += dfs(nxt, cur);
    }
    return sz[cur];
}

void hld(int cur, int p, int dep)
{
    ch[cur] = chList.size() - 1;
    chIdx[cur] = chList.back().size();
    chList.back().push_back(cur);
    num++;

    int hv = -1, hvNode = 0;
    for(int nxt : g[cur]) {
        if(nxt == p) continue;
        if(hv < sz[nxt]) {
            hv = sz[nxt];
            hvNode = nxt;
        }
    }
    if(hv != -1) {
        hld(hvNode, cur, dep);
    }
    for(int nxt : g[cur]) {
        if(nxt == p || nxt == hvNode) continue;
        chList.push_back({});
        chFirst[chList.size() - 1] = num;
        chDepth[chList.size() - 1] = dep + 1;
        hld(nxt, cur, dep + 1);
    }
}

void q1(int a)
{
    isWhite[a] = !isWhite[a];
    int ach = ch[a];
    if(isWhite[a] == true) {
        chWhiteList[ach].insert(chIdx[a]);
    } else {
        chWhiteList[ach].erase(chIdx[a]);
    }
}

int q2(int a)
{
    int ret = -1;

    int ach = ch[a];
    while(ach != 0) {
        if(chWhiteList[ach].size() > 0) {
            int firstIdx = *chWhiteList[ach].begin();
            if(firstIdx <= chIdx[a]) {
                ret = chList[ach][firstIdx];
            }
        }
        a = parent[chList[ach][0]];
        ach = ch[a];
    }

    if(chWhiteList[ach].size() > 0) {
        int firstIdx = *chWhiteList[ach].begin();
        if(firstIdx <= chIdx[a]) {
            ret = chList[ach][firstIdx];
        }
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

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);
    chList.push_back({});
    hld(1, -1, 0);
    chWhiteList.resize(chList.size());

    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if(a == 1) {
            q1(b);
        } else {
            cout << q2(b) << "\n";
        }
    }

    return 0;
}
