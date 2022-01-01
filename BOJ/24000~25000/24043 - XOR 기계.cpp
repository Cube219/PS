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

    vector<int> basis(20, 0);
    vector<int> idx;

    for(int i = 0; i < n; ++i) {
        int mask = a[i];
        while(mask > 0) {
            int msb = 0;
            for(int j = 20 - 1; j >= 0; --j) {
                if(mask & (1LL << j)) {
                    msb = j;
                    break;
                }
            }
            if(basis[msb] == 0) {
                basis[msb] = mask;
                idx.push_back(i + 1);
            }
            mask ^= basis[msb];
        }
    }

    vector<int> res;
    for(int i = 0; i < idx.size(); ++i) {
        res.push_back(idx[i]);
        res.insert(res.end(), res.begin(), prev(res.end()));
    }

    cout << res.size() << "\n";
    for(int v : res) cout << v << "\n";
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
