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
    int n;
    cin >> n;
    vector<int> d;
    while(n > 0) {
        d.push_back(n % 10);
        n /= 10;
    }
    vector<int> d2 = d;

    int mn = INF;
    int res = 0;
    auto bt = [&](auto&& self, int idx) -> void {
        if(idx == d.size()) {
            int cnt = 0;
            for(int i = 0; i < idx; ++i) {
                if(d[i] != d2[i]) cnt++;
            }
            int v = 0;
            for(int i = idx - 1; i >= 0; --i) {
                v *= 10;
                v += d2[i];
            }
            if(v % 7 == 0 && mn > cnt) {
                mn = cnt;
                res = v;
            }
            return;
        }

        int st = 0;
        if(idx == d.size() - 1) {
            st = 1;
        }
        for(int i = st; i <= 9; ++i) {
            d2[idx] = i;
            self(self, idx + 1);
        }
    };
    bt(bt, 0);

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
