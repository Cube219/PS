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

    auto get = [&](int st) {
        int nn = n;
        vector<int> res;
        while(nn > 0) {
            res.push_back(st);
            nn -= st;
            if(st == 1) st = 2;
            else st = 1;
        }
        if(nn != 0) res.clear();
        return res;
    };

    auto res = get(2);
    if(res.size() == 0) res = get(1);

    for(auto& v : res) cout << v;

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
