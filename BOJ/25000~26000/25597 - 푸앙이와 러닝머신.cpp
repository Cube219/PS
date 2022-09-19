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
    ll x, t;
    cin >> x >> t;

    vector<pair<int, int>> res;
    vector<char> use(3, false);
    vector<int> k = { 1, 4, 8 };
    vector<int> consume(3);

    auto process = [&]() {
        int remain = x;
        for(int i = 3 - 1; i >= 0; --i) {
            consume[i] = 0;
            if(use[i]) {
                consume[i] = remain / k[i];
                remain %= k[i];
            }
        }
        if(remain > 0) return;

        int sum = accumulate(consume.begin(), consume.end(), 0);
        if(sum > t) return;

        int tt = t;
        vector<pair<int, int>> r;
        for(int i = 3 - 1; i >= 0; --i) {
            if(consume[i] == 0) continue;
            r.push_back({ tt - consume[i], k[i] });
            tt -= consume[i];
        }
        if(res.empty() || res.size() > r.size()) {
            reverse(r.begin(), r.end());
            res = r;
        }
    };

    auto bt = [&](auto&& self, int idx) -> void {
        if(idx == 3) {
            process();
            return;
        }

        use[idx] = false;
        self(self, idx + 1);
        use[idx] = true;
        self(self, idx + 1);
    };
    bt(bt, 0);

    if(res.empty()) cout << "-1";
    else {
        cout << res.size() << "\n";
        for(auto [a, b] : res) cout << a << " " << b << "\n";
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
