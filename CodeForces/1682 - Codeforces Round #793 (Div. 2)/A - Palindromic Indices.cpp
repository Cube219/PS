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
    string str;
    cin >> str;

    vector<int> cnt;
    int cur = 0;
    char last = str[0];
    for(char ch : str) {
        if(last != ch) {
            cnt.push_back(cur);
            cur = 0;
        }
        last = ch;
        cur++;
    }
    cnt.push_back(cur);
    if(cnt.size() & 1) {
        cout << cnt[cnt.size() / 2] << "\n";
    } else {
        cout << "0\n";
    }
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
