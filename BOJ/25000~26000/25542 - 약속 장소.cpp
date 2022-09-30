#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, l;
    cin >> n >> l;
    vector<string> d(n);
    for(auto& v : d) cin >> v;

    string base = d[0];
    auto diff = [&](string& a, string& b) {
        int res = 0;
        for(int i = 0; i < l; ++i) if(a[i] != b[i]) res++;
        return res;
    };

    string res;
    for(int i = 0; i < l; ++i) {
        string cur = base;
        for(int j = 0; j < 26; ++j) {
            cur[i] = 'A' + j;
            bool pos = true;

            for(int k = 0; k < n; ++k) {
                if(diff(cur, d[k]) > 1) {
                    pos = false;
                    break;
                }
            }
            if(pos) {
                res = cur;
                break;
            }
        }
    }
    if(res == "") res = "CALL FRIEND";

    cout << res;
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
