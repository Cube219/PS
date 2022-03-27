#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    struct Edge
    {
        int u, v, c;
    };
    vector<Edge> eg;
    vector<map<int, int>> colors(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        if(u > v) swap(u, v);
        eg.push_back({ u, v, c });

        // auto it = colors[u].find(c);
        // if(it == colors[u].end()) it = colors[u].insert({ c, 0 }).first;
        // it->second++;
        // it = colors[v].find(c);
        // if(it == colors[v].end()) it = colors[v].insert({ c, 0 }).first;
        // it->second++;
    }

    int res = 0;
    auto add = [&](int u, int v, int newC) {
        res++;
        auto it1 = colors[u].find(newC);
        auto it2 = colors[v].find(newC);
        if(it1 == colors[u].end()) it1 = colors[u].insert({ newC, 0 }).first;
        else res--;
        if(it2 == colors[v].end()) it2 = colors[v].insert({ newC, 0 }).first;
        else res--;
        it1->second++;
        it2->second++;
    };
    auto remove = [&](int u, int v, int c) {
        res--;
        auto it1 = colors[u].find(c);
        auto it2 = colors[v].find(c);
        it1->second--;
        if(it1->second == 0) colors[u].erase(it1);
        else res++;
        it2->second--;
        if(it2->second == 0) colors[v].erase(it2);
        else res++;
    };

    for(auto [u, v, c] : eg) {
        add(u, v, c);
    }

    for(int qq = 0; qq < q; ++qq) {
        int egNum, newC;
        cin >> egNum >> newC;
        egNum--;

        auto [u, v, c] = eg[egNum];

        if(newC == c) {
            cout << res << "\n";
            continue;
        }

        remove(u, v, c);
        add(u, v, newC);
        cout << res << "\n";

        eg[egNum].c = newC;
    }
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
