#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int a, b;
    cin >> a >> b;

    int res = INF;
    auto ck = [](int aa, int bb) {
        for(int i = 20 - 1; i >= 0; --i) {
            int bit = (1 << i);
            if((aa & bit) > 0 && (bb & bit) == 0) return false;
        }
        return true;
    };
    // use b
    int ca = a, cb = b;
    int r = 0;
    while(1) {
        if(ck(ca, cb) == false) {
            cb++;
            r++;
            continue;
        } else {
            if(ca != cb) r++;
            res = r;
            break;
        }
    }

    // use a
    r = 0;
    ca = a;
    cb = b;
    while(1) {
        if(ck(ca, cb) == false) {
            ca++;
            r++;
            continue;
        } else {
            if(ca != cb) r++;
            res = min(r, res);
            break;
        }
    }

    cout << res << "\n";
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
