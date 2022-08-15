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
    int n, k;
    cin >> n >> k;
    string a, b;
    cin >> a;
    for(char ch = 'a'; ch <= 'z'; ch++) {
        int cnt = 0;
        for(char v : a) if(ch == v) cnt++;
        if(cnt > k) continue;
        for(int i = 0; i < n && cnt < k; ++i) {
            b.push_back(a[i]);
            if(a[i] != ch) cnt++;
        }
        if(cnt == k) {
            while(b.size() < n) b.push_back(ch);
            break;
        }
        b.clear();
    }

    if(b.size() == 0) b = "WRONGANSWER";
    cout << b;
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
