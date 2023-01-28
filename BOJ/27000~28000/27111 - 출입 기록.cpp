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
    cin >> n;
    vector<char> isIn(200000, false);
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b; a--;
        if(b == 1) {
            if(isIn[a]) res++;
            isIn[a] = true;
        } else {
            if(!isIn[a]) res++;
            isIn[a] = false;
        }
    }
    for(int i = 0; i < 200000; ++i) {
        if(isIn[i]) res++;
    }

    cout << res;
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
