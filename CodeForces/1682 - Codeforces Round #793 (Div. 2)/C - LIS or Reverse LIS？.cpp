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

    sort(d.begin(), d.end());
    struct Node
    {
        int v, cnt;
    };
    vector<Node> num;
    for(int v : d) {
        if(num.size() == 0 || num.back().v != v) num.push_back({ v, 0 });
        num.back().cnt++;
    }

    int one = 0, two = 0;
    for(int i = 0; i < num.size(); ++i) {
        if(num[i].cnt == 1) one++;
        else two++;
    }

    int res = 0;
    for(int i = 0; i < num.size(); ++i) {
        if(num[i].cnt == 1) one--;
        else two--;

        res = max(res, 1 + two + one / 2);

        if(num[i].cnt == 1) one++;
        else two++;
    }

    cout << res << "\n";
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
