#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int tNum;
int n;
int a[200001];
vector<pair<int, int>> d;
int aa;

ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if(b % 2 != 0) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}

ll fact[200000 + 1], invfact[200000 + 1];

void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 200000; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[200000] = pw(fact[200000], MOD - 2);
    for(int i = 200000 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;
}

ll per(int n, int r)
{
    ll factn = fact[n];
    ll invnr = invfact[n - r];
    return factn % MOD * invnr % MOD;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        sort(a, a + n);
        aa = a[0];
        for(int i = 1; i < n; ++i) {
            aa = aa & a[i];
        }

        int cur = -1;
        d.clear();
        for(int i = 0; i < n; ++i) {
            if(cur != a[i]) {
                d.push_back({ a[i], 1 });
                cur = a[i];
            } else {
                d.back().second++;
            }
        }
        ll num = 0;
        for(int i = 0; i < d.size(); ++i) {
            if(aa == d[i].first) {
                num = d[i].second;
                break;
            }
        }
        if(num < 2) {
            cout << "0\n";
        } else {
            ll res = num * (num - 1) % MOD;
            res = (res * fact[n - 2]) % MOD;
            cout << res << "\n";
        }
    }

    return 0;
}
