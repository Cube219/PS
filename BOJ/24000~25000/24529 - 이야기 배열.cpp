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
    struct Book
    {
        int v, l;
    };
    vector<vector<Book>> abc(3, vector<Book>(n));
    for(auto& v : abc[0]) cin >> v.v >> v.l;
    for(auto& v : abc[1]) cin >> v.v >> v.l;
    for(auto& v : abc[2]) cin >> v.v >> v.l;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    auto cmp = [](const Book& l, const Book& r) {
        return l.l < r.l;
    };
    sort(abc[0].begin(), abc[0].end(), cmp);
    sort(abc[1].begin(), abc[1].end(), cmp);
    sort(abc[2].begin(), abc[2].end(), cmp);

    int n2 = n + 1;
    vector<vector<int>> dp(3, vector<int>(n2 * n2 * n2, -INF));

    auto getIdx = [&](int a, int b, int c) {
        return a * n2 * n2 + b * n2 + c;
    };
    struct Tri
    {
        int a, b, c;
    };
    auto getabc = [&](int idx) -> Tri {
        Tri res;
        res.c = idx % n2;
        idx /= n2;
        res.b = idx % n2;
        res.a = idx / n2;
        return res;
    };

    for(int i = 0; i < n; ++i) {
        if(abc[0][i].l <= d[0]) dp[0][getIdx(i + 1, 0, 0)] = abc[0][i].v;
        if(abc[1][i].l <= d[0]) dp[1][getIdx(0, i + 1, 0)] = abc[1][i].v;
        if(abc[2][i].l <= d[0]) dp[2][getIdx(0, 0, i + 1)] = abc[2][i].v;
    }

    for(int i = 1; i < n; ++i) {
        vector<vector<int>> nxtdp(3, vector<int>(n2 * n2 * n2, -INF));
        // a
        for(int b = 0; b < n2; ++b) {
            for(int c = 0; c < n2; ++c) {
                int mx = -INF;
                for(int a = 1; a < n2; ++a) {
                    mx = max(mx, dp[1][getIdx(a - 1, b, c)]);
                    mx = max(mx, dp[2][getIdx(a - 1, b, c)]);

                    if(d[i] >= abc[0][a - 1].l) {
                        nxtdp[0][getIdx(a, b, c)] = mx + abc[0][a - 1].v;
                    }
                }
            }
        }

        // b
        for(int a = 0; a < n2; ++a) {
            for(int c = 0; c < n2; ++c) {
                int mx = -INF;
                for(int b = 1; b < n2; ++b) {
                    mx = max(mx, dp[0][getIdx(a, b - 1, c)]);
                    mx = max(mx, dp[2][getIdx(a, b - 1, c)]);

                    if(d[i] >= abc[1][b - 1].l) {
                        nxtdp[1][getIdx(a, b, c)] = mx + abc[1][b - 1].v;
                    }
                }
            }
        }

        // c
        for(int a = 0; a < n2; ++a) {
            for(int b = 0; b < n2; ++b) {
                int mx = -INF;
                for(int c = 1; c < n2; ++c) {
                    mx = max(mx, dp[0][getIdx(a, b, c - 1)]);
                    mx = max(mx, dp[1][getIdx(a, b, c - 1)]);

                    if(d[i] >= abc[2][c - 1].l) {
                        nxtdp[2][getIdx(a, b, c)] = mx + abc[2][c - 1].v;
                    }
                }
            }
        }

        dp = move(nxtdp);
    }

    int res = -1;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < n2 * n2 * n2; ++j) {
            res = max(res, dp[i][j]);
        }
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
