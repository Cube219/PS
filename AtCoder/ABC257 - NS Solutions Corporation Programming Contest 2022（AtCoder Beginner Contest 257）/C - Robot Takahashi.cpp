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
    struct Node
    {
        int w;
        char isA;
    };
    vector<Node> d(n);
    string str;
    cin >> str;
    for(int i = 0; i < n; ++i) {
        if(str[i] == '0') d[i].isA = false;
        else d[i].isA = true;
        cin >> d[i].w;
    }

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.w < r.w;
    });

    struct Node2
    {
        int w;
        vector<char> isA;
    };
    vector<Node2> d2;
    for(auto [w, isA] : d) {
        if(d2.size() == 0 || d2.back().w != w) d2.push_back({ w, {} });
        d2.back().isA.push_back(isA);
    }

    int res = 0;

    int lNum = 0, rNum = 0;

    for(auto& v : d2) {
        for(char isA : v.isA) {
            if(!isA) lNum++;
        }
    }
    res = lNum + rNum;

    for(int i = d2.size() - 1; i >= 0; --i) {
        for(char isA : d2[i].isA) {
            if(isA) rNum++;
            else lNum--;
        }

        res = max(res, lNum + rNum);
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
