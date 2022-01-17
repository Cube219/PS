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
    string str;
    cin >> str;
    int n = str.size();

    int idx = -1;
    for(int i = n - 2; i >= 0; --i) {
        int a = str[i] - '0';
        int b = str[i + 1] - '0';
        if(a + b >= 10) {
            idx = i;
            break;
        }
    }
    if(idx == -1) {
        idx = 0;
    }
    for(int i = 0; i < n; ++i) {
        if(idx == i) {
            int a = str[i] - '0';
            int b = str[i + 1] - '0';
            cout << a + b;
            i++;
        } else {
            cout << str[i];
        }
    }
    cout << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
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
