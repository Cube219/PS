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
    vector<vector<ll>> d(3, vector<ll>(3, 0));
    vector<vector<int>> cnt(3, vector<int>(3, 0));

    for(int i = 0; i < n; ++i) {
        string s;
        ll v;
        cin >> s >> v;

        int a, b;
        if(s[0] == 'I') a = 0;
        else if(s[0] == 'N') a = 1;
        else a = 2;
        if(s[1] == 'I') b = 0;
        else if(s[1] == 'N') b = 1;
        else b = 2;
        if(a > b) swap(a, b);

        d[a][b] += v;
        cnt[a][b]++;
    }

    ll res = 0;
    int inter = 0;
    if(cnt[0][1] > 0) inter++;
    if(cnt[0][2] > 0) inter++;
    if(cnt[1][2] > 0) inter++;

    if(inter == 0) {
        res = max(d[0][0], d[1][1]);
        res = max(res, d[2][2]);
    } else if(inter == 1) {
        int a, b, c;
        if(cnt[0][1] > 0) {
            a = 0;
            b = 1;
            c = 2;
        } else if(cnt[0][2] > 0) {
            a = 0;
            b = 2;
            c = 1;
        } else {
            a = 1;
            b = 2;
            c = 0;
        }
        res = max(d[a][a] + d[b][b] + d[a][b], d[c][c]);
    } else {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                res += d[i][j];
            }
        }
    }

    cout << res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
