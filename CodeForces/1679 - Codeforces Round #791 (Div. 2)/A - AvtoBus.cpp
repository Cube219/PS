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
    ll n;
    cin >> n;

    bool pos = true;

    ll cnt6 = n / 6;
    ll remain = n % 6;
    ll cnt4 = remain / 4;
    remain %= 4;

    ll r2 = remain;
    pos = false;
    for(int i = 0; i < 5; ++i) {
        if(remain == 0) {
            pos = true;
            break;
        }
        if(cnt6 == 0) {
            break;
        }
        cnt6--;
        remain += 6;
        cnt4 += remain / 4;
        remain %= 4;
    }

    ll mn = cnt6 + cnt4;

    cnt4 = n / 4;
    remain = n % 4;
    cnt6 = 0;
    r2 = remain;
    pos = false;
    for(int i = 0; i < 5; ++i) {
        if(remain == 0) {
            pos = true;
            break;
        }
        if(cnt4 == 0) {
            break;
        }
        cnt4--;
        remain += 4;
        cnt6 += remain / 6;
        remain %= 6;
    }
    ll mx = cnt6 + cnt4;

    if(!pos) cout << "-1\n";
    else cout << mn << " " << mx << "\n";
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
