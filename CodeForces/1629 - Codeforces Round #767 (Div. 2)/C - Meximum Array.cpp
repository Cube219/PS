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
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    vector<vector<int>> pos(n + 1);
    for(int i = n - 1; i >= 0; --i) {
        pos[a[i]].push_back(i);
    }

    vector<int> res;
    int mex = 0, i = 0;
    vector<char> has(n + 2, false);
    while(i < n) {
        if(pos[mex].size() == 0) {
            if(mex == 0) break;

            res.push_back(mex);
            for(int j = 0; j <= mex; ++j) {
                has[j] = false;
            }
            mex = 0;
            continue;
        }

        while(i < n && a[i] != mex) {
            has[a[i]] = true;
            pos[a[i]].pop_back();
            i++;
        }
        if(i == n) {

            break;
        }
        has[a[i]]++;
        pos[a[i]].pop_back();
        i++;
        while(has[mex] == true) mex++;
    }

    while(has[mex] == true) mex++;
    if(mex > 0) res.push_back(mex);

    while(i < n) {
        res.push_back(0);
        i++;
    }

    cout << res.size() << "\n";
    for(int v : res) cout << v << " ";
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
