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
    int n, m;
    cin >> n >> m;

    vector<int> tmp;
    vector<char> use(n + 1, false);
    auto bt = [&](auto&& self, int idx) -> void {
        if(idx == m) {
            for(int v : tmp) cout << v << " ";
            cout << "\n";
            return;
        }

        for(int i = 1; i <= n; ++i) {
            if(use[i]) continue;
            tmp.push_back(i);
            use[i] = true;
            self(self, idx + 1);
            use[i] = false;
            tmp.pop_back();
        }
    };
    bt(bt, 0);
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
