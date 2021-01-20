#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string.h>
using namespace std;

using lli = long long int;

int tNum;
int n, m;
int t[600001];
int stLeaf;
int pos[200001];
int nextPos;
int res;

void init()
{
    stLeaf = 1;
    while(stLeaf < n + m) {
        stLeaf *= 2;
    }
    memset(t + 1, 0, sizeof(int) * stLeaf * 2);

    for(int i = n; i >= 1; i--) {
        pos[i] = n - i;
    }

    for(int i = 0; i < n; i++) {
        int node = stLeaf + i;
        while(node > 0) {
            t[node]++;
            node /= 2;
        }
    }
    nextPos = n;
}

int p(int cl, int cr, int l, int r, int node)
{
    if(l <= cl && cr <= r) return t[node];
    else if(cr < l || r < cl) return 0;

    int m = (cl + cr) / 2;
    return p(cl, m, l, r, node * 2) + p(m + 1, cr, l, r, node * 2 + 1);
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;

        init();

        for(int i = 0; i < m; i++) {
            int a;
            cin >> a;

            res = p(0, stLeaf - 1, pos[a] + 1, stLeaf - 1, 1);
            cout << res << " ";

            int node = stLeaf + pos[a];
            while(node > 0) {
                t[node]--;
                node /= 2;
            }
            node = stLeaf + nextPos;
            while(node > 0) {
                t[node]++;
                node /= 2;
            }
            pos[a] = nextPos;
            nextPos++;
        }

        cout << "\n";
    }

    return 0;
}
