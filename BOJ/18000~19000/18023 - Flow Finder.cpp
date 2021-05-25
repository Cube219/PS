#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[300001];
ll flow[300001];
int u[300001]; // unknowns in leaf node
vector<ll> uv; // unknown values
bool pos = true;

struct RNode
{
    ll f;
    int unum;
    int u;
};
RNode emptyNode;

RNode dfs(int cur, int par)
{
    RNode ret;
    ret.f = 0;
    ret.unum = 0;
    ret.u = 0;
    bool haschild = false;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        haschild = true;
        RNode r = dfs(nxt, cur);
        if(pos == false) return emptyNode;

        ret.f += r.f;
        if(r.unum > 0) {
            ret.u = r.u;
            ret.unum += r.unum;
        }
    }

    if(flow[cur] == 0) {
        if(haschild == false) {
            int unknown = uv.size();
            uv.push_back(-1);
            u[cur] = unknown;

            ret.f = 0;
            ret.u = unknown;
            ret.unum = 1;
        } else {
            flow[cur] = ret.f;
        }
    } else {
        if(haschild == false) {
            ret.f = flow[cur];
        } else {
            ll remainf = flow[cur] - ret.f;
            if(ret.unum == 0) {
                if(remainf != 0) {
                    pos = false;
                    return emptyNode;
                }
            } else if(ret.unum == 1) {
                if(remainf <= 0) {
                    pos = false;
                    return emptyNode;
                }
                uv[ret.u] = remainf;
                ret.f = flow[cur];
                ret.unum = 0;
                ret.u = 0;
            } else {
                if(remainf != ret.unum) {
                    pos = false;
                    return emptyNode;
                }
                ret.f = flow[cur];
                ret.unum = 0;
                ret.u = 0;
            }
        }
    }
    return ret;
}

ll dfs2(int cur, int par)
{
    ll f = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        f += dfs2(nxt, cur);
    }
    if(f == 0) {
        if(flow[cur] == 0) {
            if(uv[u[cur]] == -1) uv[u[cur]] = 1;
            flow[cur] = uv[u[cur]];
        }
    } else {
        flow[cur] = f;
    }
    return flow[cur];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 2; i <= n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    for(int i = 1; i <= n; ++i) {
        cin >> flow[i];
    }
    RNode ret = dfs(1, -1);
    if(ret.unum > 0) pos = false;
    else {
        if(pos == true) dfs2(1, -1);
    }

    if(pos == false) {
        cout << "impossible";
    } else {
        for(int i = 1; i <= n; ++i) {
            cout << flow[i] << "\n";
        }
    }

    return 0;
}
