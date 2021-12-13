#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<vector<int>> g(n), g2(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dep(n), par(n);
    dep[0] = 0;
    par[0] = 0;
    auto dfs = [&](auto&& self, int cur, int p) -> void {
        for(int nxt : g[cur]) {
            if(nxt == p) continue;
            dep[nxt] = dep[cur] + 1;
            par[nxt] = cur;
            self(self, nxt, cur);
        }
    };
    dfs(dfs, 0, -1);

    vector<ll> d(n, 0);
    auto query = [&](int a, int b) {
        vector<int> apath, bpath;
        while(dep[a] != dep[b]) {
            if(dep[a] > dep[b]) {
                apath.push_back(a);
                a = par[a];
            } else {
                bpath.push_back(b);
                b = par[b];
            }
        }
        while(a != b) {
            apath.push_back(a);
            a = par[a];
            bpath.push_back(b);
            b = par[b];
        }
        apath.push_back(a);

        ll num = 0;
        for(int i = 0; i < apath.size(); ++i) {
            d[apath[i]] += num;
            num++;
        }
        for(int i = bpath.size() - 1; i >= 0; --i) {
            d[bpath[i]] += num;
            num++;
        }
    };

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int t, a, b;
        cin >> t;
        if(t == 1) {
            cin >> a >> b;
            a--; b--;
            query(a, b);
        } else {
            cin >> a;
            a--;
            cout << d[a] << "\n";
        }
    }

    return 0;
}
