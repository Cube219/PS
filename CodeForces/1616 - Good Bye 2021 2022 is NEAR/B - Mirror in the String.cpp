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
    string str;
    cin >> n >> str;
    if(n >= 2 && str[0] == str[1]) {
        cout << str[0] << str[1] << "\n";
        return;
    }

    int res = n - 1;
    for(int i = 0; i < n - 1; ++i) {
        if(str[i] < str[i + 1]) {
            res = i;
            break;
        }
    }
    string r;
    for(int i = 0; i <= res; ++i) {
        r.push_back(str[i]);
    }
    for(int i = res; i >= 0; --i) {
        r.push_back(str[i]);
    }
    bool f = true;
    for(int i = 0; i < r.size() - 1; ++i) {
        if(r[i] != r[i + 1]) {
            f = false;
            break;
        }
    }
    if(f == true) {
        char ch = r[0];
        r.clear();
        r.push_back(ch);
        r.push_back(ch);
    }

    cout << r << "\n";
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
