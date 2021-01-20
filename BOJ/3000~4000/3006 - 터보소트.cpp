#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;

int n, a[100001];
int t[300001];
int leafStart;
int res[100001];

int g(int cl, int cr, int l, int r, int node)
{
    if(l <= cl && cr <= r) return t[node];
    else if(cr < l || r < cl) return 0;

    int m = (cl + cr) / 2;
    return g(cl, m, l, r, node * 2) + g(m + 1, cr, l, r, node * 2 + 1);
}

void rm(int node)
{
    while(node > 0) {
        t[node]--;
        node /= 2;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for(int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        a[tmp] = i;
    }

    leafStart = 1;
    while(leafStart < n) {
        leafStart *= 2;
    }
    for(int i = 0; i < n; i++) {
        t[leafStart + i] = 1;
    }
    for(int i = leafStart - 1; i >= 1; i--) {
        t[i] = t[i * 2] + t[i * 2 + 1];
    }

    int si = 1, ei = n, resI = 0;
    while(si <= ei) {
        res[resI++] = g(0, leafStart - 1, 0, a[si] - 1, 1);
        rm(leafStart + a[si]);
        si++;

        res[resI++] = g(0, leafStart - 1, a[ei] + 1, n - 1, 1);
        rm(leafStart + a[ei]);
        ei--;
    }

    for(int i = 0; i < n; i++) {
        cout << res[i] << "\n";
    }

    return 0;
}
