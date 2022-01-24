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
    vector<int> d(3);
    for(auto& v : d) cin >> v;

    if(d[0] + d[1] + d[2] != 180) {
        cout << "Error";
        return;
    }
    int cnt = 0;
    if(d[0] == d[1]) cnt++;
    if(d[0] == d[2]) cnt++;
    if(d[1] == d[2]) cnt++;

    if(cnt == 3) cout << "Equilateral";
    else if(cnt == 1) cout << "Isosceles";
    else cout << "Scalene";
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
