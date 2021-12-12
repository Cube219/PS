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
    vector<int> x(n + 1), y(n + 1), e(n + 1);
    for(int i = 0; i <= n; ++i) {
        cin >> x[i] >> y[i] >> e[i];
    }

    int res = 0;
    vector<int> d(n + 1, 0);
    for(int i = 1; i <= n; ++i) {
        d[i] = max(0, e[0] - abs(x[i] - x[0]) - abs(y[i] - y[0]));
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int v = max(0, e[j] - abs(x[j] - x[i]) - abs(y[j] - y[i]));
            d[i] -= v;
        }
    }
    for(int i = 1; i <= n; ++i) {
        res = max(res, d[i]);
    }

    if(res == 0) cout << "IMPOSSIBLE";
    else cout << res;

    return 0;
}
