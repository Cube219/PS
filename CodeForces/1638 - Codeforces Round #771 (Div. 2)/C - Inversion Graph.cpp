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
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    vector<vector<int>> d2;
    for(auto& v : d) {
        if(d2.size() == 0 || d2.back().back() < v) d2.emplace_back();
        d2.back().push_back(v);
    }

    // vector<int> mx(d2.size()), mn(d2.size());
    // for(int i = 0; i < d2.size(); ++i) {
    //     mx[i] = -1;
    //     mn[i] = INF;
    //     for(int v : d2[i]) {
    //         mx[i] = max(mx[i], v);
    //         mn[i] = min(mn[i], v);
    //     }
    // }

    vector<int> mx, mn;
    for(auto& list : d2) {
        int cmx = 0, cmn = INF;
        for(auto& v : list) {
            cmx = max(cmx, v);
            cmn = min(cmn, v);
        }
        while(mx.size() > 0 && mx.back() > cmn) {
            cmx = max(cmx, mx.back());
            cmn = min(cmn, mn.back());
            mx.pop_back();
            mn.pop_back();
        }
        mx.push_back(cmx);
        mn.push_back(cmn);
    }


    cout << mx.size() << "\n";
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
