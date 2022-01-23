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
    vector<vector<int>> d(n, vector<int>(n));
    for(auto& v1 : d) {
        for(auto& v2 : v1) {
            cin >> v2;
        }
    }

    vector<int> val;
    vector<vector<int>> idx(n, vector<int>(n, -1));
    auto process = [&]() {
        for(int step = 0; step < n; step += 2) {
            int i = step, j = 0;
            while(i < n - 1) {
                if(i == j) {
                    int cur = d[i][j];
                    if(i > 0)
                        cur ^= idx[i - 1][j];

                    idx[i + 1][j] = cur;
                    idx[i][j + 1] = cur;
                    val.push_back(cur);
                } else {
                    int cur = d[i][j] ^ d[j][i];
                    // left
                    if(j > 0) {
                        cur ^= idx[i][j - 1];
                    }
                    // right
                    cur ^= idx[i][j + 1];
                    // up
                    cur ^= idx[i - 1][j];

                    idx[i + 1][j] = idx[j][i + 1] = cur;
                    val.push_back(cur);
                }

                i++;
                j++;
            }
        }
    };
    process();
    for(int i = 0; i < n; ++i) {
        reverse(d[i].begin(), d[i].end());
        reverse(idx[i].begin(), idx[i].end());
    }
    process();

    int res = 0;
    for(int v : val) res ^= v;
    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
