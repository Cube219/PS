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
int n, k, v, cnt;
int a[100001], d[100001];
vector<int> g[100001];

int dfs(int cur, int par)
{
    d[cur] = a[cur];
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        d[cur] ^= dfs(nxt, cur);
    }
    if(d[cur] == v && cur != 0) {
        cnt++;
        d[cur] = 0;
    }
    return d[cur];
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
        for(int i = 0; i < n; ++i) {
            g[i].clear();
            d[i] = 0;
        }
        cnt = 0;

        cin >> n >> k;

        v = 0;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
            v ^= a[i];
        }
        for(int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        if(v == 0) {
            cout << "YES\n";
            continue;
        }

        dfs(0, -1);

        if(cnt < 2 || k == 2) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }

    return 0;
}
