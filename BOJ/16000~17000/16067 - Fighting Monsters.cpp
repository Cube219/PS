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
    vector<int> d(1000001, -1), one;
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        d[v] = i + 1;
        if(v == 1) one.push_back(i + 1);
    }

    if(one.size() > 1) {
        cout << one[0] << " " << one[1];
        return;
    }

    int a = 1, b = 2;
    while(b <= 1000000) {
        if(d[a] != -1 && d[b] != -1) {
            cout << d[a] << " " << d[b];
            return;
        }
        int c = a + b;
        a = b;
        b = c;
    }
    cout << "impossible";
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
