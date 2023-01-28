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
    for(auto& v : d) {
        cin >> v;
        v--;
    }

    vector<int> gNum;
    vector<char> visit(n, false);
    for(int i = 0; i < n; ++i) {
        if(visit[i]) continue;

        int cur = i, cnt = 0;
        while(!visit[cur]) {
            cnt++;
            visit[cur] = true;
            cur = d[cur];
        }
        gNum.push_back(cnt);
    }

    ll base = 0;
    for(int v : gNum) {
        if(v == 1) base++;
        else base += 2 * v + (v - 2);
    }

    ll res = 0;
    // 같은 그룹에서 swap
    for(int v : gNum) {
        if(v == 1) continue;

        res += (base - 2) * v * (v - 1) / 2;
    }

    // 다른 그룹에서 swap
    ll sum = 0;
    for(int v : gNum) {
        res += (base + 2) * sum * v;
        sum += v;
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
