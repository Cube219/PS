#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
#include <map>
using namespace std;

using ll = long long int;

int n;
vector<int> g[250001];
int c[250001];
bool hasparc[250001];
int cnum[250001], totalcnum[250001];
int num[250001];
int num2;

ll r1, r2, r3;

struct Node
{
    int sz;
    map<int, int> mp;
};

Node dfs(int cur, int par)
{
    Node has;
    has.sz = 0;

    for(int nxt : g[cur]) {
        if(nxt == par) continue;

        auto chas = dfs(nxt, cur);
        if(chas.mp.find(c[cur]) != chas.mp.end()) {
            hasparc[nxt] = true;
            if(num[cur] == 0) num2++;
            num[cur]++;
        }
        if(has.mp.size() < chas.mp.size()) {
            swap(has.sz, chas.sz);
            swap(has.mp, chas.mp);
        }
        for(auto& v : chas.mp) {
            auto it = has.mp.find(v.first);
            if(it == has.mp.end()) it = has.mp.insert({ v.first, 0 }).first;
            it->second += v.second;
        }
        has.sz += chas.sz;
    }
    auto it = has.mp.find(c[cur]);
    if(it == has.mp.end()) it = has.mp.insert({ c[cur], 0 }).first;
    it->second++;
    has.sz++;

    cnum[cur] = it->second;

    return has;
}

void dfs2(int cur, int par)
{
    if(num2 == 0) {
        r1++;
        r2 += cur + 1;
        r3 += (ll)(cur + 1) * (ll)(cur + 1);
    }

    if(num[cur] == 1) {
        int nx = -1;
        for(int nxt : g[cur]) {
            if(nxt == par) continue;
            if(hasparc[nxt] == true) {
                nx = nxt;
                break;
            }
        }
        assert(nx != -1);

        num[cur]--;
        num2--;

        if(cnum[nx] - totalcnum[c[nx]] == 0) {
            dfs2(nx, cur);
        }

        num[cur]++;
        num2++;
    } else {
        for(int nxt : g[cur]) {
            if(nxt == par) continue;

            if(cnum[nxt] - totalcnum[c[nxt]] == 0) {
                dfs2(nxt, cur);
            }
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
        totalcnum[c[i]]++;
    }
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0, -1);

    bool pos = true;
    for(int i = 0; i < n; ++i) {
        if(num[i] > 1) {
            pos = false;
            break;
        }
    }
    if(pos == true) {
        dfs2(0, -1);
    }
    cout << r1 << "\n";
    cout << r2 << "\n";
    cout << r3 << "\n";

    return 0;
}
