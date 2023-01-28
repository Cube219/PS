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
    struct Node { int ed, num; };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.ed >> v.num;

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.ed > r.ed;
    });

    bool pos = true;
    int cur = 1, extra = 0;
    while(!d.empty()) {
        auto& [ed, num] = d.back();

        if(num == 0) {
            d.pop_back();
            continue;
        }

        if(ed < cur) {
            extra += num;
            num = 0;
            if(extra > ed) {
                pos = false;
                break;
            }
            continue;
        }

        if(cur % 7 != 6 && cur % 7 != 0) {
            num--;
        }
        cur++;
    }

    if(!pos) cout << "-1";
    else cout << extra;
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
