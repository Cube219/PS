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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; ++i) cin >> a[i] >> b[i];

    vector<int> has(m, n);
    vector<int> res(n);
    for(int i = n - 1; i >= 0; --i) {
        a[i]--; b[i]--;

        int cur = i;
        while(1) {
            if(has[a[cur]] > cur) {
                swap(has[a[cur]], cur);
            } else if(has[b[cur]] > cur) {
                swap(has[b[cur]], cur);
            } else break;
            if(cur == n) {
                res[i]++;
                break;
            }
        }

        if(i > 0) res[i - 1] = res[i];
    }

    for(int v : res) cout << v << "\n";
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
