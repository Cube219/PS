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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n;
        cin >> n;
        vector<vector<int>> g(n);
        vector<int> d(n), per(n), g2(n);

        int rt = -1;
        for(int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            p--;
            if(i == p) rt = p;
            else {
                g[p].push_back(i);
                g2[i] = p;
            }
        }
        for(int i = 0; i < n; ++i) {
            int v;
            cin >> v;
            d[v - 1] = i;
            per[i] = v - 1;
        }

        bool pos = true;
        auto dfs = [&](auto&& self, int cur) {
            for(int nxt : g[cur]) {
                if(d[cur] > d[nxt]) {
                    pos = false;
                    return;
                }
                self(self, nxt);
            }
        };
        dfs(dfs, rt);
        if(pos == false) {
            cout << "-1\n";
            continue;
        }
        vector<int> cost(n, 0), res(n, 0);
        for(int i = 0; i < n; ++i) {
            int st = per[i];
            if(st == rt) continue;

            int par = g2[st];
            res[st] = 1;
            if(i > 0) res[st] = max(res[st], cost[per[i - 1]] - cost[par] + 1);
            cost[st] = cost[par] + res[st];
        }

        for(int i = 0; i < n; ++i) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
