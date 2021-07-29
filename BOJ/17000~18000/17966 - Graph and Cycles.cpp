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
vector<int> e[1001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int m = n * (n - 1) / 2;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        e[a].push_back(c);
        e[b].push_back(c);
    }

    for(int i = 0; i < n; ++i) {
        sort(e[i].begin(), e[i].end());
    }

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < n - 1; j += 2) {
            res += e[i][j];
        }
    }

    cout << res;

    return 0;
}
