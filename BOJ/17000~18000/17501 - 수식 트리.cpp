#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n * 2 - 1);
    vector<vector<int>> g(n * 2 - 1);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    vector<char> hasPar(n * 2 - 1, false);
    for(int i = n; i < n * 2 - 1; ++i) {
        char op;
        int u, v;
        cin >> op >> u >> v;
        u--; v--;
        if(op == '+') d[i] = 1;
        else d[i] = -1;

        g[i].push_back(u);
        g[i].push_back(v);
        hasPar[u] = true;
        hasPar[v] = true;
    }

    int rt = 0;
    for(int i = n; i < n * 2 - 1; ++i) {
        if(hasPar[i] == false) {
            rt = i;
            break;
        }
    }

    vector<int> op(n, 1);
    auto dfs = [&](auto&& self, int cur, int curop) -> void {
        if(g[cur].size() == 2) {
            // left
            self(self, g[cur][0], curop);
            // right
            if(d[cur] == 1) self(self, g[cur][1], curop);
            else self(self, g[cur][1], curop * -1);
        } else {
            op[cur] = curop;
        }
    };
    dfs(dfs, rt, 1);

    int res = 0;
    vector<int> pos, neg;
    for(int i = 0; i < n; ++i) {
        if(op[i] == 1) pos.push_back(d[i]);
        else neg.push_back(d[i]);
        res += d[i] * op[i];
    }
    sort(pos.begin(), pos.end(), [](const int& l, const int& r) {
        return l > r;
    });
    sort(neg.begin(), neg.end());

    while(pos.size() > 0 && neg.size() > 0) {
        int pv = pos.back();
        int nv = neg.back();
        pos.pop_back();
        neg.pop_back();

        if(pv > nv) break;
        res -= pv * 2;
        res += nv * 2;
    }

    cout << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
