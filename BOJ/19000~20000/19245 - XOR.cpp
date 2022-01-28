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
    ll all = 0;
    vector<ll> basis(60, 0);
    for(int i = 0; i < n; ++i) {
        ll v;
        cin >> v;
        all ^= v;

        int msb = 60 - 1;
        while(v > 0) {
            while((v & (1LL << msb)) == 0) {
                msb--;
            }
            if(basis[msb] == 0) {
                basis[msb] = v;
                break;
            }
            v ^= basis[msb];
            msb--;
        }
    }
    for(int i = 0; i < 60; ++i) {
        if(basis[i] > 0) {
            for(int j = i + 1; j < 60; ++j) {
                if(basis[j] & (1LL << i)) basis[j] ^= basis[i];
            }
        }
    }

    vector<char> skip(60, false);
    for(int i = 0; i < 60; ++i) {
        if((all & (1LL << i)) == 0) skip[i] = true;
    }
    ll res = 0;
    vector<ll> basis2(60, 0);
    for(int i = 60 - 1; i >= 0; --i) {
        if(skip[i] == false) {
            res = basis[i];

            for(int j = 0; j < 60; ++j) {
                if(i == j) continue;
                ll v = basis[j];
                for(int k = i; k >= 0; --k) {
                    if(skip[k] == false && v & (1LL << k)) {
                        if(basis2[k] == 0) {
                            basis2[k] = v;
                            break;
                        }
                        v ^= basis2[k];
                    }
                }
            }

            for(int j = i - 1; j >= 0; --j) {
                if(res & (1LL << j)) res ^= basis2[j];
            }
            break;
        }
    }

    cout << abs(res - (all ^ res)) << "\n";
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
