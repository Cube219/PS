#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <map>
#include <set>
using namespace std;

using ll = long long int;

int n;
vector<int> g[100001];

int dfs(int cur, int par, int k)
{
    // map<int, int> d;
    multiset<int> d;
    int kcnt = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        int t = dfs(nxt, cur, k);
        if(t == -1) return -1;

        if(t < k) {
            d.insert(t);
        } else {
            kcnt++;
        }
    }

    int remainCnt = 0;
    int maxRemain = 0;
    while(d.size() > 0) {
        int v = *d.begin();
        d.erase(d.begin());

        auto it = d.lower_bound(k - v);
        if(it != d.end()) {
            d.erase(it);
        } else {
            remainCnt++;
            maxRemain = max(maxRemain, v);
        }
    }

    if(remainCnt < kcnt) {
        return k + 1;
    } else if(remainCnt == kcnt) {
        if(cur == 1) return k + 1; // success
        else return maxRemain + 1;
    } else if(remainCnt == kcnt + 1) {
        return maxRemain + 1;
    } else {
        return -1;
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
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int l = 1, r = n + 1;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        int res = dfs(1, -1, m);
        if(res >= m || res == 1) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l;

    return 0;
}
