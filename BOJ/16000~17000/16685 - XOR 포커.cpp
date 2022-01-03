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
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    vector<ll> basis(60, 0);
    vector<int> cnt(60, 0);
    for(ll mask : d) {
        int curcnt = 1;
        while(mask > 0) {
            int msb;
            for(msb = 60 - 1; msb >= 0; --msb) {
                if(mask & (1LL << msb)) break;
            }

            if(basis[msb] == 0) {
                basis[msb] = mask;
                cnt[msb] = curcnt;
                break;
            }
            mask ^= basis[msb];
            curcnt ^= cnt[msb];
        }
    }

    ll res = 0;
    int rcnt = 0;
    int least = 0;
    for(int i = 60 - 1; i >= 0; --i) {
        if(cnt[i] == 1) least = i;

        if(res > (res ^ basis[i])) continue;
        res ^= basis[i];
        rcnt ^= cnt[i];
    }

    if(rcnt == 1) {
        bool f = false;
        for(ll v : d) {
            int vcnt = 0;
            for(int i = 60 - 1; i >= 0; --i) {
                if(v & (1LL << i)) {
                    v ^= basis[i];
                    vcnt ^= cnt[i];
                }
            }
            if(vcnt == 0) {
                f = true;
                break;
            }
        }
        if(f == false) {
            res = 0;
            for(int i = 60 - 1; i >= 0; --i) {
                if(i != least) {
                    if(res > (res ^ basis[i])) continue;
                } else {
                    if(res < (res ^ basis[i])) continue;
                }
                res ^= basis[i];
            }
        }
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
