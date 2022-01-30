#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
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
    vector<int> d(n * 2);
    for(auto& v : d) cin >> v;

    int mn = INF, mn2 = INF, idx = 0;
    for(int i = 0; i < n; ++i) {
        if(mn > d[i]) {
            mn = d[i];
            mn2 = d[i + n];
            idx = i;
        } else if(mn == d[i] && mn2 > d[i + n]) {
            mn2 = d[i + n];
            idx = i;
        }
    }
    vector<int> res;
    if(mn >= mn2) {
        res.push_back(idx);
    } else {
        int st = 0;
        for(int i = 0; i < n; ++i) {
            if(d[i] > mn)  continue;
            st = i;
            res.push_back(i);
        }
        bool addSame = false;
        if(res.size() > 1 && d[res[0] + n] < d[res[1] + n]) addSame = true;

        vector<int> tmp;
        for(int i = st + 1; i < n; ++i) {
            if(addSame == false && d[i] == d[res[0] + n]) continue;
            if(d[i] > d[res[0] + n]) continue;

            while(tmp.size() > 0 && d[tmp.back()] > d[i]) tmp.pop_back();
            tmp.push_back(i);
        }
        res.insert(res.end(), tmp.begin(), tmp.end());
    }

    for(int i = 0; i < res.size(); ++i) {
        cout << d[res[i]] << " ";
    }
    for(int i = 0; i < res.size(); ++i) {
        cout << d[res[i] + n] << " ";
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
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
