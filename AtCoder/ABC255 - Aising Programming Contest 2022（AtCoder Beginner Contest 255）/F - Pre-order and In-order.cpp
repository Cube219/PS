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
    vector<int> pre(n), in(n);
    for(auto& v : pre) cin >> v;
    for(auto& v : in) cin >> v;

    vector<int> pos(n + 1);
    for(int i = 0; i < n; ++i) {
        pos[in[i]] = i;
    }

    bool ck = true;
    vector<int> lch(n + 1, 0), rch(n + 1, 0);
    int idx = 0;
    auto dnc = [&](auto&& self, int l, int r) -> int {
        int i = idx++;
        if(i >= n) {
            ck = false;
            return 0;
        }
        int npos = pos[pre[i]];
        // Left
        int nl, nr;
        nl = l;
        nr = npos - 1;
        if(nl <= nr) lch[pre[i]] = self(self, nl, nr);
        // Right
        nl = npos + 1;
        nr = r;
        if(nl <= nr) rch[pre[i]] = self(self, nl, nr);

        return pre[i];
    };
    dnc(dnc, 0, n - 1);

    if(pre[0] != 1) ck = false;

    if(!ck) cout << "-1";
    else {
        for(int i = 1; i <= n; ++i) {
            cout << lch[i] << " " << rch[i] << "\n";
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
