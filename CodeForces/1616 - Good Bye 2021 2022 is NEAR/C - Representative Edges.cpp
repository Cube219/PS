#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <numeric>
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

    vector<char> ck(n, false);
    int res = INF;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            fill(ck.begin(), ck.end(), false);
            int gap = a[j] - a[i];
            int igap = j - i;

            ll g = gcd(gap, igap);
            gap /= g;
            igap /= g;

            ck[i] = ck[j] = true;
            int cur = a[i];

            for(int k = i + igap; k < n; k += igap) {
                cur += gap;
                if(a[k] == cur) ck[k] = true;
            }

            cur = a[j];
            for(int k = j - igap; k >= 0; k -= igap) {
                cur -= gap;
                if(a[k] == cur) ck[k] = true;
            }

            int r = 0;
            for(int k = 0; k < n; ++k) {
                if(ck[k] == false) r++;
            }
            res = min(res, r);
        }
    }
    if(n == 1) res = 0;
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
