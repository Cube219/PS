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
    int l, n;
    cin >> l >> n;
    vector<string> d(n);
    for(auto& v : d) cin >> v;

    sort(d.begin(), d.end());

    vector<string> res, cur(l);
    auto ck = [&]() {
        bool f = true;
        for(int i = 0; i < l; ++i) {
            for(int j = i; j < l; ++j) {
                if(cur[i][j] != cur[j][i]) {
                    f = false;
                    break;
                }
            }
            if(f == false) break;
        }
        return f;
    };

    vector<char> use(n, false);
    auto bt = [&](auto&& self, int idx) -> void {
        if(idx == l) {
            if(ck()) {
                res = move(cur);
            }
            return;
        }

        for(int i = 0; i < n; ++i) {
            if(use[i]) continue;

            use[i] = true;
            cur[idx] = d[i];
            self(self, idx + 1);

            if(res.size() > 0) return;
            use[i] = false;
        }
    };
    bt(bt, 0);

    if(res.size() == 0) {
        cout << "NONE";
    } else {
        for(int i = 0; i < l; ++i) {
            cout << res[i] << "\n";
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
