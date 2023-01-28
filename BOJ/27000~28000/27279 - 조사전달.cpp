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
    vector<int> a(n), b(m);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    bool res = true;
    while(!a.empty()) {
        int v = a.back(); a.pop_back();

        while(!b.empty() && b.back() == 0) b.pop_back();
        if(b.empty()) break;

        if(b.size() > v) {
            res = false;
            break;
        }
        b.back()--;
    }

    if(res) cout << "YES";
    else cout << "NO";
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
