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
vector<pair<int, int>> res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    int f = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= i; ++j) {
            res.push_back({ f + 1, j });
        }
        f = 1 - f;
    }
    for(int j = 1; j <= n; ++j) {
        res.push_back({ f + 1, j });
    }
    f = 1 - f;
    for(int i = n; i >= 1; --i) {
        for(int j = n - i + 1; j <= n; ++j) {
            res.push_back({ f + 1, j });
        }
        f = 1 - f;
    }
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i].first << " " << res[i].second << "\n";
    }

    return 0;
}
