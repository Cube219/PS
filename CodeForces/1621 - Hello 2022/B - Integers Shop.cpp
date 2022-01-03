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
    vector<int> l(n), r(n), c(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i] >> c[i];
    }

    vector<ll> res(n), res2(n, LNF);
    int cl = INF, cr = -1;
    ll lcost = 0, rcost = 0, tcost = LNF;
    int lidx = -1, ridx = -1;
    for(int i = 0; i < n; ++i) {
        bool changed = false;
        if(l[i] < cl) {
            lcost = c[i];
            cl = l[i];
            lidx = i;
            changed = true;
        } else if(l[i] == cl && lcost > c[i]) {
            lcost = c[i];
            cl = l[i];
            lidx = i;
        }

        if(cr < r[i]) {
            rcost = c[i];
            cr = r[i];
            ridx = i;
            changed = true;
        } else if(cr == r[i] && rcost > c[i]) {
            rcost = c[i];
            cr = r[i];
            ridx = i;
        }

        if(changed == true){
            tcost = LNF;
        }

        if(cl == l[i] && r[i] == cr) {
            tcost = min(tcost, (ll)c[i]);
        }

        cout << min(lcost + rcost, tcost) << "\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
