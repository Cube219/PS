#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, q;
vector<int> g[100001];
int parent[100001][30];
int len[100001];

void dfs(int cur, int par, int cnt)
{
    parent[cur][0] = par;
    len[cur] = cnt;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        dfs(nxt, cur, cnt + 1);
    }
}

int lca(int a, int b)
{
    if(len[a] > len[b]) {
        swap(a, b);
    }
    int gap = len[b] - len[a];
    int idx = 0;
    while(gap > 0) {
        if(gap % 2 == 1) {
            b = parent[b][idx];
        }
        idx++;
        gap /= 2;
    }
    if(a != b) {
        for(int j = 30; j >= 0; j--) {
            if(parent[a][j] != 0 && parent[b][j] != 0 && parent[a][j] != parent[b][j]) {
                a = parent[a][j];
                b = parent[b][j];
            }
        }

        a = parent[a][0];
    }
    return a;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, -1, 0);

    for(int i = 1; i < 30; ++i) {
        for(int j = 0; j < n; ++j) {
            int tmp = parent[j][i - 1];
            if(tmp != -1) {
                parent[j][i] = parent[tmp][i - 1];
            }
        }
    }

    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        int lc = lca(a, b);
        int l = len[a] + len[b] - len[lc] * 2;
        if(l % 2 == 0) cout << "Town\n";
        else cout << "Road\n";
    }

    return 0;
}
