#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
int t[300001], lazy[300001];
int stLeaf;
vector<int> g[100001];
int st[100001], ed[100001];

int cnt;
void dfs(int cur, int parent)
{
    st[cur] = cnt++;
    for(int nxt : g[cur]) {
        if(nxt == parent) continue;
        dfs(nxt, cur);
    }
    ed[cur] = cnt - 1;
}

void propagate(int l, int r, int node)
{
    if(lazy[node] == 0) return;

    if(node < stLeaf) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    t[node] += (r - l + 1) * lazy[node];
    lazy[node] = 0;
}

int find(int cl, int cr, int l, int r, int node)
{
    propagate(cl, cr, node);
    if(l <= cl && cr <= r) return t[node];
    else if(cr < l || r < cl) return 0;
    int m = (cl + cr) / 2;
    return find(cl, m, l, r, node * 2) + find(m + 1, cr, l, r, node * 2 + 1);
}

void add(int cl, int cr, int l, int r, int node, int v)
{
    propagate(cl, cr, node);
    if(l <= cl && cr <= r) {
        lazy[node] += v;
        propagate(cl, cr, node);
        return;
    } else if(cr < l || r < cl) return;
    int m = (cl + cr) / 2;
    add(cl, m, l, r, node * 2, v);
    add(m + 1, cr, l, r, node * 2 + 1, v);
    t[node] = t[node * 2] + t[node * 2 + 1];
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < n; ++i) {
        int parent;
        cin >> parent;
        g[parent - 1].push_back(i);
    }

    dfs(0, -1);

    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a;
        if(a == 1) {
            cin >> b >> c;
            b--;
            add(0, stLeaf - 1, st[b], ed[b], 1, c);
        } else {
            cin >> b;
            b--;
            cout << find(0, stLeaf - 1, st[b], st[b], 1) << "\n";
        }
    }

    return 0;
}
