#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#ifndef CUBE_PS
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif


#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    vector<vector<int>> table(n + 1, vector<int>(18, 0));
    for(int i = 0; i < n; ++i) {
        table[i][0] = a[i];
    }
    for(int j = 1; j < 18; ++j) {
        for(int i = 0; i + (1 << (j - 1)) < n; ++i) {
            table[i][j] = gcd(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }

    vector<int> lg2;
    lg2.resize(n + 1);
    lg2[0] = lg2[1] = 0;
    for(int i = 2; i <= n; ++i) {
        lg2[i] = lg2[i / 2] + 1;
    }

    auto query = [&](int l, int r) -> int {
        int j = lg2[r - l + 1];
        return gcd(table[l][j], table[r - (1 << j) + 1][j]);
    };

    int res = 0;
    int liml = -1;
    for(int i = 0; i < n; ++i) {
        if(a[i] == 1) {
            res++;
            liml = i;
            cout << res << " ";
            continue;
        }

        int l = liml, r = i;
        while(l + 1 < r) {
            int mid = (l + r) / 2;
            int g = query(mid, i);
            int rng = i - mid + 1;
            if(g == rng) {
                res++;
                liml = i;
                break;
            }
            if(g > rng) r = mid;
            else l = mid;
        }
        cout << res << " ";
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
