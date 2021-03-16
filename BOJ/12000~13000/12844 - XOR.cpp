#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, m;
int t[1100000], lazy[1100000];
int stLeaf;

void propagate(int l, int r, int node)
{
    if(lazy[node] == 0) return;
    if(node < stLeaf) {
        lazy[node * 2] ^= lazy[node];
        lazy[node * 2 + 1] ^= lazy[node];
    }
    if(node >= stLeaf) {
        t[node] ^= lazy[node];
    }
    lazy[node] = 0;
}

int find(int cl, int cr, int l, int r, int node)
{
    propagate(cl, cr, node);
    if(l <= cl && cr <= r) {
        return t[node];
    } else if(cr < l || r < cl) return 0;
    int m = (cl + cr) / 2;
    return find(cl, m, l, r, node * 2) ^ find(m + 1, cr, l, r, node * 2 + 1);
}

void insert(int cl, int cr, int l, int r, int node, int k)
{
    propagate(cl, cr, node);
    if(l <= cl && cr <= r) {
        lazy[node] ^= k;
        propagate(cl, cr, node);
        return;
    } else if(cr < l || r < cl) return;
    int m = (cl + cr) / 2;
    insert(cl, m, l, r, node * 2, k);
    insert(m + 1, cr, l, r, node * 2 + 1, k);
    t[node] = t[node * 2] ^ t[node * 2 + 1];
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    stLeaf = 1;
    while(stLeaf < n) stLeaf *= 2;
    for(int i = 0; i < n; ++i) {
        cin >> t[stLeaf + i];
    }
    for(int i = stLeaf - 1; i > 0; --i) {
        t[i] = t[i * 2] ^ t[i * 2 + 1];
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c, d;
        cin >> a;
        if(a == 1) {
            cin >> b >> c >> d;
            insert(0, stLeaf - 1, b, c, 1, d);
        } else {
            cin >> b >> c;
            cout << find(0, stLeaf - 1, b, c, 1) << "\n";
        }
    }

    return 0;
}
