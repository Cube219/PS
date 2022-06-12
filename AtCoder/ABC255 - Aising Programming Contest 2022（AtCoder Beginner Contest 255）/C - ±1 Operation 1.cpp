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
    ll x, a, d, n;
    cin >> x >> a >> d >> n;

    x -= a;

    ll st = 0;
    ll ed = (n - 1) * d;
    if(st > ed) swap(st, ed);
    if(x < st) cout << st - x;
    else if(ed < x) cout << x - ed;
    else {
        if(d == 0) {
            cout << abs(x);
        } else {
            if(d < 0) {
                x *= -1;
                d *= -1;
            }
            x %= d;
            cout << min(x, d - x);
        }
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
