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
    int n;
    cin >> n;
    vector<int> d1, d2;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if(a & 1) d1.push_back(a);
        else d2.push_back(a);
    }
    bool res = true;
    for(int i = 0; i < (int)d1.size() - 1; ++i) {
        if(d1[i] > d1[i + 1]) res = false;
    }
    for(int i = 0; i < (int)d2.size() - 1; ++i) {
        if(d2[i] > d2[i + 1]) res = false;
    }

    if(res) cout << "Yes\n";
    else cout << "No\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
