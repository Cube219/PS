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
    string str;
    cin >> str;

    int n = str.size();

    auto lcs = [](string& l, string r) {
        int n = l.size();
        int m = r.size();
        if (n == 0 || m == 0) return 0;

        vector<int> cur(m, 0);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> nxt(m);
            for(int j = 0; j < m; ++j) {
                nxt[j] = cur[j];
                if (j > 0) nxt[j] = max(nxt[j], nxt[j - 1]);
                if (l[i] == r[j]) nxt[j] = max(nxt[j], (j > 0 ? cur[j - 1] : 0) + 1);
            }
            res = max(res, nxt[m - 1]);
            cur = move(nxt);
        }

        return res;
    };

    int n2 = n / 2;
    string l = str.substr(0, n2);
    string r = str.substr(n2, n - n2);
    int res = min(n2, n - n2) - lcs(l, r);

    if (n % 2 == 1) {
        int n2 = n / 2 + 1;
        l = str.substr(0, n2);
        r = str.substr(n2, n - n2);
        res = max(res, min(n2, n - n2) - lcs(l, r));
    }

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
