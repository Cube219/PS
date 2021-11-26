#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> s(n), b(n);
    for(int i = 0; i < n; ++i) {
        s[i].resize(k);
        b[i].resize(k);
        for(int j = 0; j < k; ++j) {
            cin >> b[i][j] >> s[i][j];
        }
    }
    vector<vector<ll>> g(n, vector<ll>(n, INF));
    for(int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g[u][v] = c;
    }
    for(int k = 0; k < n; ++k) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
    }
    vector<vector<int>> p(n, vector<int>(n, 0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            for(int z = 0; z < k; ++z) {
                if(i == j || b[i][z] == -1 || s[j][z] == -1) continue;
                p[i][j] = max(p[i][j], s[j][z] - b[i][z]);
            }
        }
    }

    vector<vector<ll>> g2(n, vector<ll>(n));
    auto ck = [&](ll v) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                g2[i][j] = INF;
                if(i != j && g[i][j] != INF) {
                    g2[i][j] = v * g[i][j] - p[i][j];
                }
            }
        }

        for(int k = 0; k < n; ++k) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < n; ++j) {
                    g2[i][j] = min(g2[i][j], g2[i][k] + g2[k][j]);
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            if(g2[i][i] <= 0) return true;
        }

        return false;
    };

    ll lo = 0, hi = 1000000100;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(ck(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << lo;

    return 0;
}
