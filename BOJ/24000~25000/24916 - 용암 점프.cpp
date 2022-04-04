#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <assert.h>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

bool fail[22][22];

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    if(n > 22) {
        for(int i = 0; i < n; ++i) cout << "NO\n";
        return;
    }

    int mn = INF;
    for(int i = 0; i < n - 1; ++i) mn = min(mn, d[i + 1] - d[i]);

    for(int i = 0; i < n; ++i) {
        int lr = INF;
        if(i > 0) lr = min(lr, d[i] - d[i - 1]);
        if(i < n - 1) lr = min(lr, d[i + 1] - d[i]);
        if(lr > mn) {
            cout << "NO\n";
            continue;
        }

        vector<int> l(1, -INF), r(1, INF);
        for(int j = 0; j < i; ++j) l.push_back(d[j]);
        for(int j = n - 1; j >= i + 1; --j) r.push_back(d[j]);

        for(int i1 = 0; i1 < l.size(); ++i1) {
            for(int i2 = 0; i2 < r.size(); ++i2) {
                fail[i1][i2] = false;
            }
        }

        int res = 0;
        auto bt = [&](auto&& self, vector<int> cl, vector<int> cr, int pos, int lastJump) -> void {
            auto& curfail = fail[(int)cl.size() - 1][(int)cr.size() - 1];
            if(curfail) return;

            while(cl.size() > 1 || cr.size() > 1) {
                int lDis = pos - cl.back();
                int rDis = cr.back() - pos;

                if(min(lDis, rDis) < lastJump * 2) {
                    curfail = true;
                    return;
                }

                if(lDis < rDis) {
                    lastJump = lDis;
                    pos = cl.back();
                    cl.pop_back();
                } else if(lDis > rDis) {
                    lastJump = rDis;
                    pos = cr.back();
                    cr.pop_back();
                } else {
                    // Move left
                    if(fail[(int)cl.size() - 2][(int)cr.size() - 1] == false) {
                        lastJump = lDis;
                        pos = cl.back();
                        auto newl = cl;
                        newl.pop_back();
                        self(self, newl, cr, pos, lastJump);
                        if(res == 1) return;
                    }

                    // Move right
                    if(fail[(int)cl.size() - 1][(int)cr.size() - 2] == false) {
                        lastJump = rDis;
                        pos = cr.back();
                        auto newr = cr;
                        newr.pop_back();
                        self(self, cl, newr, pos, lastJump);
                        if(res == 1) return;
                    }

                    curfail = true;
                    return;
                }
            }
            res = 1;
        };
        bt(bt, l, r, d[i], 0);

        if(res == 1) cout << "YES\n";
        else cout << "NO\n";
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
