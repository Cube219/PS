#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Range
{
    int l, r;
};

int n;
int v[10001], maxv;
vector<int> g[10001];
vector<Range> rng[10001];
vector<int> tmp[103];
bool has[103][103];

void dfs(int cur)
{
    for(int nxt : g[cur]) {
        dfs(nxt);
    }

    for(int i = 0; i < maxv; ++i) {
        tmp[i].clear();
        for(int j = 0; j < maxv; ++j) {
            has[i][j] = false;
        }
    }
    for(int nxt : g[cur]) {
        for(Range r : rng[nxt]) {
            tmp[r.l].push_back(r.r);
        }
    }

    for(int l = maxv - 1; l >= 1; --l) {
        if(l == v[cur]) {
            for(int i = l + 1; i < maxv; ++i) {
                if(has[l + 1][i] == true) has[l][i] = true;
            }
            has[l][l] = true;
        } else {
            for(int r : tmp[l]) {
                if(l <= v[cur] && v[cur] <= r) continue;
                for(int i = r + 1; i < maxv; ++i) {
                    if(has[r + 1][i] == true) has[l][i] = true;
                }
                has[l][r] = true;
            }
        }
    }

    for(int l = 1; l <= v[cur]; ++l) {
        for(int r = v[cur]; r < maxv; ++r) {
            if(has[l][r] == true) {
                rng[cur].push_back({ l, r });
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
        cin >> v[i];
        maxv = max(maxv, v[i] + 1);
    }
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    dfs(0);
    cout << rng[0].size();

    return 0;
}
