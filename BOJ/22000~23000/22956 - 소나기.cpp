#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, q;
int h[1001][1001];
int par[1000001];
int mn[1000001], mnidx[1000001], mnq[1000001];
bool w[1001][1001];
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };

int find(int v)
{
    vector<int> st;
    while(v != par[v]) {
        st.push_back(v);
        v = par[v];
    }
    for(int x : st) par[x] = v;
    return v;
}

void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;

    if(mn[ar] == mn[br]) {
        if(mnq[ar] > mnq[br]) {
            mnidx[ar] = mnidx[br];
            mnq[ar] = mnq[br];
        }
    } else if(mn[ar] > mn[br]){
        mn[ar] = mn[br];
        mnidx[ar] = mnidx[br];
        mnq[ar] = mnq[br];
    }
    par[br] = ar;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> h[i][j];
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int idx = i * m + j;
            par[idx] = idx;
            mn[idx] = h[i][j];
            mnidx[idx] = idx;
        }
    }

    for(int i = 1; i <= q; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;

        w[a][b] = true;
        h[a][b] -= c;
        for(int j = 0; j < 4; ++j) {
            int na = a + dx[j];
            int nb = b + dy[j];
            if(na < 0 || nb < 0 || na >= n || nb >= m) continue;
            if(w[na][nb] == false) continue;

            uni(a * m + b, na * m + nb);
        }

        int rt = find(a * m + b);
        if(mn[rt] > h[a][b]) {
            mn[rt] = h[a][b];
            mnidx[rt] = a * m + b;
            mnq[rt] = i;
        }

        int x = mnidx[rt] / m;
        int y = mnidx[rt] % m;
        cout << x + 1 << " " << y + 1 << "\n";
    }

    return 0;
}
