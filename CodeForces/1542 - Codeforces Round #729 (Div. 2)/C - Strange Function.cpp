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
ll n;

ll gcd(ll a, ll b)
{
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        ll cur = 2;
        ll res = n * 2;
        res %= MOD;
        for(ll i = 2; i <= 1000; ++i) {
            if(cur % i != 0) {
                ll g = gcd(cur, i);
                cur = cur * i / g;
            }
            res += n / cur;
            res %= MOD;
            if(n / cur == 0) break;
        }
        cout << res << "\n";
    }

    return 0;
}
