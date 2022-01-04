#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    vector<char> pos(n, true);
    for(int i = 0; i < n; ++i) {
        if((a[i] | k) != k) pos[i] = false;
    }
    int cur = 0, l = 0, r = -1;
    for(int i = 0; i < n; ++i) {
        if(pos[i] == false) {
            cur = 0;
            l = i + 1;
            continue;
        }
        cur |= a[i];
        if(cur == k) {
            r = i;
            break;
        }
    }
    
    if(r == -1) cout << "-1";
    else cout << l + 1 << " " << r + 1;
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
