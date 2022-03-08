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
    int h;
    cin >> h;
    vector<ll> st(h);
    st[0] = 1;
    for(int i = 1; i < h; ++i) {
        st[i] = st[i - 1] + i;
    }

    auto getLR = [&](ll x) -> pair<int, int> {
        int idx = upper_bound(st.begin(), st.end(), x) - st.begin() - 1;

        ll l = x - st[idx];
        return {l, l + h - idx };
    };

    int q1, q2;
    cin >> q1 >> q2;
    vector<double> d(h + 2, 0);
    for(int i = 0; i < q1; ++i) {
        ll x, num;
        cin >> x >> num;
        auto [l, r] = getLR(x);

        double ex = (double)num / (r - l + 1);
        d[l] += ex;
        d[r + 1] -= ex;
    }

    for(int i = 1; i < h + 2; ++i) {
        d[i] += d[i - 1];
    }
    vector<double> sum(h + 2);
    sum[0] = d[0];
    for(int i = 1; i < h + 2; ++i) {
        sum[i] = sum[i - 1] + d[i];
    }

    for(int i = 0; i < q2; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        double res = sum[r];
        if(l > 0) res -= sum[l - 1];
        cout << res << "\n";
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
