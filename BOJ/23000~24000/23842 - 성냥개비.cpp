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
    vector<int> num = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

    int n;
    cin >> n;
    n -= 4;

    bool res = false;
    vector<int> d(6);
    auto bt = [&](auto&& self, int idx, int remain) -> void {
        if(idx == 6) {
            if(remain != 0) return;
            int a = d[0] * 10 + d[1];
            int b = d[2] * 10 + d[3];
            int c = d[4] * 10 + d[5];
            if(a + b == c) {
                cout << d[0] << d[1] << "+" << d[2] << d[3] << "=" << d[4] << d[5];
                res = true;
            }
        } else {
            for(int i = 0; i < 10; ++i) {
                d[idx] = i;
                if(remain - num[i] < 0) continue;
                self(self, idx + 1, remain - num[i]);
                if(res == true) return;
            }
        }
    };
    bt(bt, 0, n);

    if(res == false) cout << "impossible";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
