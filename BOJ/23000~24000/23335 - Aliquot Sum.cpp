#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    vector<ll> res(1000001, 1);
    res[1] = 0;
    for(int i = 2; i <= 1000000; ++i) {
        for(int j = i * 2; j <= 1000000; j += i) {
            res[j] += i;
        }
    }

    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        if(res[v] > v) cout << "abundant\n";
        else if(res[v] < v) cout << "deficient\n";
        else cout << "perfect\n";
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