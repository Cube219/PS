#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
vector<int> g[200001];
ll d[200001], depth[200001];
bool oddcycle;

bool visit[200001];
ll dfs(int cur, int par, int dep)
{
    visit[cur] = true;
    depth[cur] = dep;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        if(visit[nxt] == true) {
            if((dep - depth[nxt] >= 2) && (dep - depth[nxt]) % 2 == 0) {
                oddcycle = true;
            }
            continue;
        }
        d[cur] += dfs(nxt, cur, dep + 1);
    }
    return -d[cur];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            ll a;
            cin >> a;
            d[i] = a;
        }
        for(int i = 0; i < n; ++i) {
            ll b;
            cin >> b;
            d[i] -= b;
        }
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        ll res = dfs(0, -1, 0);
        if(res == 0) cout << "YES\n";
        else {
            res = abs(res);
            if(res % 2 == 1) cout << "NO\n";
            else {
                if(oddcycle == true) cout << "YES\n";
                else cout << "NO\n";
            }
        }

        for(int i = 0; i < n; ++i) {
            g[i].clear();
            visit[i] = false;
            depth[i] = 0;
        }
        oddcycle = false;
    }

    return 0;
}
