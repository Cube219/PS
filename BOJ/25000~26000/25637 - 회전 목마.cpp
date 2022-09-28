#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
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

    int res = INF;
    for(int i = 0; i < n; ++i) {
        struct Node { int idx, cnt; };
        vector<Node> more;
        vector<int> zero;
        int v = 0;
        for(int j = 0; j < n; ++j) {
            int k = (i + j) % n;
            if(d[k] == 0) {
                if(more.size() > 0) {
                    v += j - more.back().idx;
                    more.back().cnt--;
                    if(more.back().cnt == 0) more.pop_back();
                } else {
                    zero.push_back(j);
                }
            } else if(d[k] > 1) {
                int remain = d[k] - 1;
                while(zero.size() > 0 && remain > 0) {
                    v += j - zero.back();
                    zero.pop_back();
                    remain--;
                }
                if(remain > 0) {
                    more.push_back({ j, remain });
                }
            }
        }
        res = min(res, v);
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
