#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct GNode
{
    int nxt;
    ll cost;
};

struct Node
{
    int cnt;
    ll sum;
    ll sqsum;
};

int n;
vector<GNode> g[100001];
ll d[100001];
ll res;

void dfs(int cur, int par, ll cost)
{
    d[cur] = cost;
    for(auto& nx : g[cur]) {
        if(nx.nxt == par) continue;
        dfs(nx.nxt, cur, cost + nx.cost);
    }
}

Node dfs2(int cur, int par)
{
    vector<Node> r;
    for(auto& nx : g[cur]) {
        if(nx.nxt == par) continue;

        r.push_back(dfs2(nx.nxt, cur));
    }

    if(r.size() == 0) {
        return { 1, d[cur], d[cur] * d[cur] };
    } else if(r.size() == 1) {
        return r[0];
    }

    Node a = r[0];
    Node b = r[1];
    ll v = d[cur];
    a.sqsum = a.sqsum + (v * v) * a.cnt - a.sum * v * 2;
    a.sum -= v * a.cnt;
    b.sqsum = b.sqsum + (v * v) * b.cnt - b.sum * v * 2;
    b.sum -= v * b.cnt;

    res += b.cnt * a.sqsum + a.sum * b.sum * 2 + a.cnt * b.sqsum;

    r[0].cnt += r[1].cnt;
    r[0].sum += r[1].sum;
    r[0].sqsum += r[1].sqsum;
    return r[0];
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
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    int rt = 0;
    for(int i = 0; i < n; ++i) {
        if(g[i].size() == 1) {
            rt = i;
            break;
        }
    }

    dfs(rt, -1, 0);
    auto r = dfs2(rt, -1);
    res += r.sqsum;

    cout << res;

    return 0;
}
