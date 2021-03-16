#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, m;
int t[300001], lazy[300001];
int stLeaf;

void propagate(int l, int r, int node)
{
    if(lazy[node] == 0) return;
    if(node < stLeaf) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }
    if(lazy[node] % 2 == 1) {
        t[node] = (r - l + 1) - t[node];
    }
    lazy[node] = 0;
}

void p(int cl, int cr, int l, int r, int node)
{
    propagate(cl, cr, node);
    if(l <= cl && cr <= r) {
        lazy[node]++;
        propagate(cl, cr, node);
        return;
    }
    else if(cr < l || r < cl) return;
    int m = (cl + cr) / 2;
    p(cl, m, l, r, node * 2);
    p(m + 1, cr, l, r, node * 2 + 1);
    t[node] = t[node * 2] + t[node * 2 + 1];
}

int find(int cl, int cr, int l, int r, int node)
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

    int n, m;
    cin >> n >> m;
    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 0) {
            p(0, stLeaf - 1, b - 1, c - 1, 1);
        } else {
            cout << find(0, stLeaf - 1, b - 1, c - 1, 1) << "\n";
        }
    }

    return 0;
}
