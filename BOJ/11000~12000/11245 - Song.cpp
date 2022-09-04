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
    using vvi = vector<vector<int>>;
    vector<vector<int>> d(26, vector<int>(26));
    for(auto& v : d) for(auto& v2 : v) cin >> v2;

    auto mul = [](const vvi& a, const vvi& b) {
        vvi res(26, vector<int>(26, 0));
        for(int i = 0; i < 26; ++i) {
            for(int j = 0; j < 26; ++j) {
                for(int k = 0; k < 26; ++k) {
                    res[i][j] = max(res[i][j], a[i][k] + b[k][j]);
                }
            }
        }
        return res;
    };

    int n;
    cin >> n;
    for(int q = 0; q < n; ++q) {
        char ch; int l;
        cin >> ch >> l;
        if(l == 0) cout << "0\n";
        else {
            auto cur = d;
            vvi mat(26, vector<int>(26, 0));
            for(int i = 0; i < 26; ++i) mat[i][i] = 0;
            for(l--; l > 0; l >>= 1) {
                if(l & 1) mat = mul(cur, mat);
                cur = mul(cur, cur);
            }

            int res = 0;
            for(int i = 0; i < 26; ++i) {
                res = max(res, mat[ch - 'A'][i]);
            }
            cout << res << "\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
