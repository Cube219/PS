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
    string str;
    cin >> n >> str;

    bool f = true;
    for(int i = 0; i < n; ++i) {
        if(str[i] != str[n - i - 1]) {
            f = false;
            break;
        }
    }
    if(f) {
        cout << "Yes";
        return;
    }

    if(n >= 3 && (str[0] == 'B' || str[n - 1] == 'A')) cout << "Yes";
    else cout << "No";
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
