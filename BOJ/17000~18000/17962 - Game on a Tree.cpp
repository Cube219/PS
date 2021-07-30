#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[100001];

int p(int cur, int par)
{
    int ret = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        ret += p(nxt, cur);
    }
    if(ret == 0) return 1;
    else return ret - 1;
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
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int res = p(0, -1);
    if(res == 0) cout << "Bob";
    else cout << "Alice";

    return 0;
}
