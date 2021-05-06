#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int a, b;
};

int n;
Node d[250001];
vector<int> vv;
vector<int> g[500001];
ll res;

int getv(int v)
{
    return lower_bound(vv.begin(), vv.end(), v) - vv.begin();
}

bool visit[500001];
int edgenum;
vector<int> l;
void dfs(int cur, int par)
{
    l.push_back(cur);
    visit[cur] = true;
    for(int nxt : g[cur]) {
        if(nxt == par || visit[nxt] == true) continue;
        dfs(nxt, cur);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b };
        vv.push_back(a);
        vv.push_back(b);
    }
    sort(vv.begin(), vv.end());
    vv.erase(unique(vv.begin(), vv.end()), vv.end());
    for(int i = 0; i < n; ++i) {
        int a = getv(d[i].a);
        int b = getv(d[i].b);
        d[i].a = a;
        d[i].b = b;

        g[a].push_back(b);
        g[b].push_back(a);
        edgenum++;
    }

    for(int i = 0; i < vv.size(); ++i) {
        if(visit[i] == true) continue;
        l.clear();
        dfs(i, -1);

        edgenum = 0;
        for(int j = 0; j < l.size(); ++j) {
            edgenum += g[l[j]].size();
        }
        edgenum /= 2;
        if(edgenum == l.size()) {
            for(int j = 0; j < l.size(); ++j) {
                res += (ll)vv[l[j]] * (g[l[j]].size() - 1);
            }
        } else {
            int maxl = -1;
            for(int j = 0; j < l.size(); ++j) {
                maxl = max(maxl, l[j]);
            }
            for(int j = 0; j < l.size(); ++j) {
                int cnt;
                if(l[j] == maxl) {
                    cnt = g[l[j]].size();
                } else {
                    cnt = g[l[j]].size() - 1;
                }
                res += (ll)vv[l[j]] * cnt;
            }
        }
    }

    cout << res;

    return 0;
}
