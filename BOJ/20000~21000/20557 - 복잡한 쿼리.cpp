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
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<pair<int, int>>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int> d(n, -1), cycles;
    d[0] = 0;
    auto dfs = [&](auto&& self, int cur) -> void {
        for(auto [nxt, w] : g[cur]) {
            if(d[nxt] != -1) {
                cycles.push_back(d[cur] ^ d[nxt] ^ w);
            } else {
                d[nxt] = d[cur] ^ w;
                self(self, nxt);
            }
        }
    };
    dfs(dfs, 0);

    vector<int> basis(30, 0);
    for(int v : cycles) {
        for(int i = 30 - 1; i >= 0; --i) {
            if(v & (1 << i)) {
                if(basis[i] == 0) {
                    basis[i] = v;
                    break;
                }
                v ^= basis[i];
            }
        }
    }
    for(int i = 0; i < 30; ++i) {
        if(basis[i] == 0) continue;
        for(int j = i + 1; j < 30; ++j) {
            if(basis[j] & (1 << i)) basis[j] ^= basis[i];
        }
    }
    vector<vector<int>> bitsum(30, vector<int>(n, 0));
    for(int i = 0; i < 30; ++i) {
        int bit = 1 << i;
        for(int j = 0; j < n; ++j) {
            if(d[j] & bit) bitsum[i][j]++;
        }
        for(int j = 1; j < n; ++j) {
            bitsum[i][j] += bitsum[i][j - 1];
        }
    }
    vector<int> xorsum(n);
    xorsum[0] = d[0];
    for(int i = 1; i < n; ++i) {
        xorsum[i] = d[i] ^ xorsum[i - 1];
    }

    for(int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        int res = 0;
        if((r - l + 1) % 2 == 0) {
            res = xorsum[r];
            if(l > 0) res ^= xorsum[l - 1];
        }

        for(int j = 0; j < 30; ++j) {
            int bit1num = bitsum[j][r];
            if(l > 0) bit1num -= bitsum[j][l - 1];
            int bit0num = (r - l + 1) - bit1num;

            ll pairodd = 0;
            // n개의 서로 다른 pair의 개수가 홀수인 경우: (mod 4)가 2또는 3
            if(bit1num % 4 == 2 || bit1num % 4 == 3) pairodd++;
            if(bit0num % 4 == 2 || bit0num % 4 == 3) pairodd++;
            pairodd %= 2;

            if(pairodd == 1) res ^= basis[j];
        }

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
