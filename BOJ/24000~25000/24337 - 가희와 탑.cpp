#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> res;
    for(int i = 1; i < a; ++i) {
        res.push_back(i);
    }
    if(a >= b) {
        res.push_back(a);
    } else {
        res.push_back(b);
    }
    for(int i = b - 1; i >= 1; --i) {
        res.push_back(i);
    }
    if(res.size() > n) {
        cout << "-1";
        return;
    }
    if(a > 1) {
        for(int i = 0; i < n - res.size(); ++i) {
            cout << "1 ";
        }
        for(int v : res) {
            cout << v << " ";
        }
    } else {
        cout << res[0] << " ";
        for(int i = 0; i < n - res.size(); ++i) {
            cout << "1 ";
        }
        for(int i = 1; i < res.size(); ++i) {
            cout << res[i] << " ";
        }
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
