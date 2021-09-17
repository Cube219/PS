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
bool isleg[100001];
bool isbody[100001];

int p(int cur)
{
    int ret = 0;
    int lnum = 0, num = 0;
    for(int nxt : g[cur]) {
        ret += p(nxt);
        if(isleg[nxt] == true) lnum++;
        if(isbody[nxt] == false) num++;
    }
    if(lnum > 0 && num >= 3 && cur != 0) {
        ret++;
        isbody[cur] = true;
    } else if(num >= 2) {
        isleg[cur] = true;
    }
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n - 1; ++i) {
        int v;
        cin >> v;
        v--;
        g[v].push_back(i);
    }

    cout << p(0);

    return 0;
}
