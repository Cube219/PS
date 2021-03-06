#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, m, k;
int stLeaf;
ll t[3000001];
ll lazy[3000001];

void propagate(int l, int r, int node)
{
    if(lazy[node] == 0) return;
    if(node < stLeaf) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    t[node] += lazy[node] * (ll)(r - l + 1);
    lazy[node] = 0;
}

void add(int cl, int cr, int l, int r, int node, ll v)
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

ll find(int cl, int cr, int l, int r, int node)
{
    propagate(cl, cr, node);
    if(l <= cl && cr <= r) return t[node];
    else if(cr < l || r < cl) return 0;
    int m = (cl + cr) / 2;
    return find(cl, m, l, r, node * 2) + find(m + 1, cr, l, r, node * 2 + 1);
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < n; ++i) {
        cin >> t[stLeaf + i];
    }
    for(int i = stLeaf - 1; i > 0; --i) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
    for(int i = 0; i < m + k; ++i) {
        int a, b, c;
        ll d;
        cin >> a;
        if(a == 1) {
            cin >> b >> c >> d;
            add(0, stLeaf - 1, b - 1, c - 1, 1, d);
        } else {
            cin >> b >> c;
            cout << find(0, stLeaf - 1, b - 1, c - 1, 1) << "\n";
        }
    }

    return 0;
}
