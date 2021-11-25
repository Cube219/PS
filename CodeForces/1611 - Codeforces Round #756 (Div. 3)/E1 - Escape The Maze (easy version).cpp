#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int cur;
    int cost;
};

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
        int n, k;
        cin >> n >> k;
        vector<int> x(k);
        for(auto& v : x) {
            cin >> v;
            v--;
        }
        vector<vector<int>> g(n);
        for(int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }

        queue<Node> q;
        vector<int> d(n, -1);
        for(int i = 0; i < k; ++i) {
            q.push({ x[i], 0 });
            d[x[i]] = 0;
        }
        while(q.empty() == false) {
            Node cur = q.front();
            q.pop();

            for(int nxt : g[cur.cur]) {
                if(d[nxt] != -1) continue;
                d[nxt] = cur.cost + 1;
                q.push({ nxt, cur.cost + 1 });
            }
        }

        bool res = false;
        auto dfs = [&](auto&& self, int cur, int par, int cost) {
            if(cur != 0 && g[cur].size() == 1) {
                res = true;
                return;
            }
            for(int nxt : g[cur]) {
                if(nxt == par) continue;
                if(d[nxt] <= cost + 1) continue;
                self(self, nxt, cur, cost + 1);
                if(res == true) break;
            }
        };
        dfs(dfs, 0, -1, 0);

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
