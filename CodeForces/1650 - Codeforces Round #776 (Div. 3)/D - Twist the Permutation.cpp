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
    vector<int> a(n);
    for(auto& v : a) {
        cin >> v;
        v--;
    }

    vector<int> pos(n);
    for(int i = 0; i < n; ++i) {
        pos[a[i]] = i;
    }

    vector<int> res(n);
    for(int i = n - 1; i >= 1; --i) {
        int mv = (pos[i] + 1) % (i + 1);
        res[i] = mv;
        for(int j = 0; j < i; ++j) {
            pos[j] -= mv;
            if(pos[j] < 0) pos[j] += (i + 1);
        }
    }

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
