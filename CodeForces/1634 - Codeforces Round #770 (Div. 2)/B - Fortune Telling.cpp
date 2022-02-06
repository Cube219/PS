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
    ll n, x, y;
    cin >> n >> x >> y;

    int num = 0;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        num += a & 1;
    }
    num %= 2;
    if(num == 0) {
        if((x & 1) == (y & 1)) cout << "Alice\n";
        else cout << "Bob\n";
    } else {
        if((x & 1) != (y & 1)) cout << "Alice\n";
        else cout << "Bob\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
